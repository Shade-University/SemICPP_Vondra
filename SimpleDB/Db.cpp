#include "dbapi.h"

const std::string Db::dbLocation = "databases/";

Db* Db::open(std::string database)
{
	std::string path = dbLocation + database; // databases/userDb -> datab�ze p�edstavuje slo�ku
	CreateDirectory(dbLocation.c_str(), NULL);
	CreateDirectory(path.c_str(), NULL); //Postupn� vytvo� slo�ky pokud neexistuj�


	Db* db = new Db();
	db->databaseName = database;
	return db; //Vytvo� Db a nastav jej� jm�no
}

// Vytvo�� novou tabulku
Table* Db::createTable(std::string name, int fieldsCount, FieldObject** fields)
{
	std::string file = dbLocation + databaseName + "/" + name + ".schema"; // databases/userDb/users.schema -> users.schema p�edstavuje tabulku
	std::ofstream ofs(file, std::ifstream::trunc);

	ofs << fieldsCount << std::endl;
	for (int i = 0; i < fieldsCount; i++)
	{
		ofs << fields[i]->getName() << ";" << std::to_string((int)fields[i]->getType()) << std::endl;
	} //P�i vytvo�en� zapi� pouze hlavi�ku a po�et sloupc�

	return new Table(fields, fieldsCount, file);
}
// Otev�e existuj�c� tabulku
Table* Db::openTable(std::string name)
{
	int fieldsCount;
	std::string file = dbLocation + databaseName + "/" + name + ".schema";
	std::ifstream ifile(file);

	std::string line;
	std::getline(ifile, line); //Na�ti po�et sloupc�
	fieldsCount = std::stoi(line);

	FieldObject** fields = new FieldObject *[fieldsCount];
	for (int i = 0; i < fieldsCount; i++)
	{
		std::getline(ifile, line);
		int separatorPosition = line.find(';');
		std::string fieldName = line.substr(0, separatorPosition);
		int fieldType = std::stoi(line.substr(separatorPosition + 1, line.length()));
		FieldType type = static_cast<FieldType>(fieldType);
		//Na�ti ��dek a rozparsuj
		//Struktura hlavi�ky v souboru je: nazev;typ [pomoc� enum ��sla]

		FieldObject* fieldObject = Db::Field(fieldName, type);
		fields[i] = fieldObject;
	} //Na�ti hlavi�ku

	std::vector<Object**> data;
	std::vector<std::string> tokens;
	std::string word;
	while (std::getline(ifile, line))
	{
		tokens.clear();
		std::stringstream s(line);

		while (std::getline(s, word, ';')) {
			tokens.push_back(word);
		} //P�eve� ��dek na stream ten rozparsuj podle separ�toru ;
		//Z�sk�me hodnoty ve sloupc�ch

		Object** row = new Object *[fieldsCount];
		for (int j = 0; j < fieldsCount; j++)
		{
			switch (fields[j]->getType())
			{
			case FieldType::String: row[j] = Db::String(tokens[j]); break;
			case FieldType::Integer: row[j] = Db::Int(std::stoi(tokens[j])); break;
			case FieldType::Double: row[j] = Db::Double(std::stod(tokens[j])); break;
			}
		} //Podle typu hodnot, kter� zn�me z hlavi�ky vytvo� objekty
		data.push_back(row); //��dky uchov�v�m ve vectoru (nepot�ebuji zn�t jejich velikost)
	}

	return new Table(fields, fieldsCount, file, data);
}

Table* Db::openOrCreateTable(std::string name, int fieldsCount, FieldObject** fields)
{
	Table* table;
	std::string path = dbLocation + databaseName + "/" + name + ".schema";
	std::ifstream ifile(path);

	if (ifile.fail()) //Zjist�, jestli soubor [tabulka] ji� existuje a podle toho se zavol� p��slu�n� metoda
	{
		table = this->createTable(name, fieldsCount, fields);
	}
	else
	{
		table = this->openTable(name);
	}

	return table;
}