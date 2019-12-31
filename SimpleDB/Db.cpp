#include "dbapi.h"

const std::string Db::dbLocation = "databases/";

Db* Db::open(std::string database)
{
	std::string path = dbLocation + database; // databases/userDb -> databáze pøedstavuje složku
	CreateDirectory(dbLocation.c_str(), NULL);
	CreateDirectory(path.c_str(), NULL); //Postupnì vytvoø složky pokud neexistují


	Db* db = new Db();
	db->databaseName = database;
	return db; //Vytvoø Db a nastav její jméno
}

// Vytvoøí novou tabulku
Table* Db::createTable(std::string name, int fieldsCount, FieldObject** fields)
{
	std::string file = dbLocation + databaseName + "/" + name + ".schema"; // databases/userDb/users.schema -> users.schema pøedstavuje tabulku
	std::ofstream ofs(file, std::ifstream::trunc);

	ofs << fieldsCount << std::endl;
	for (int i = 0; i < fieldsCount; i++)
	{
		ofs << fields[i]->getName() << ";" << std::to_string((int)fields[i]->getType()) << std::endl;
	} //Pøi vytvoøení zapiš pouze hlavièku a poèet sloupcù

	return new Table(fields, fieldsCount, file);
}
// Otevøe existující tabulku
Table* Db::openTable(std::string name)
{
	int fieldsCount;
	std::string file = dbLocation + databaseName + "/" + name + ".schema";
	std::ifstream ifile(file);

	std::string line;
	std::getline(ifile, line); //Naèti poèet sloupcù
	fieldsCount = std::stoi(line);

	FieldObject** fields = new FieldObject *[fieldsCount];
	for (int i = 0; i < fieldsCount; i++)
	{
		std::getline(ifile, line);
		int separatorPosition = line.find(';');
		std::string fieldName = line.substr(0, separatorPosition);
		int fieldType = std::stoi(line.substr(separatorPosition + 1, line.length()));
		FieldType type = static_cast<FieldType>(fieldType);
		//Naèti øádek a rozparsuj
		//Struktura hlavièky v souboru je: nazev;typ [pomocí enum èísla]

		FieldObject* fieldObject = Db::Field(fieldName, type);
		fields[i] = fieldObject;
	} //Naèti hlavièku

	std::vector<Object**> data;
	std::vector<std::string> tokens;
	std::string word;
	while (std::getline(ifile, line))
	{
		tokens.clear();
		std::stringstream s(line);

		while (std::getline(s, word, ';')) {
			tokens.push_back(word);
		} //Pøeveï øádek na stream ten rozparsuj podle separátoru ;
		//Získáme hodnoty ve sloupcích

		Object** row = new Object *[fieldsCount];
		for (int j = 0; j < fieldsCount; j++)
		{
			switch (fields[j]->getType())
			{
			case FieldType::String: row[j] = Db::String(tokens[j]); break;
			case FieldType::Integer: row[j] = Db::Int(std::stoi(tokens[j])); break;
			case FieldType::Double: row[j] = Db::Double(std::stod(tokens[j])); break;
			}
		} //Podle typu hodnot, který známe z hlavièky vytvoø objekty
		data.push_back(row); //Øádky uchovávám ve vectoru (nepotøebuji znát jejich velikost)
	}

	return new Table(fields, fieldsCount, file, data);
}

Table* Db::openOrCreateTable(std::string name, int fieldsCount, FieldObject** fields)
{
	Table* table;
	std::string path = dbLocation + databaseName + "/" + name + ".schema";
	std::ifstream ifile(path);

	if (ifile.fail()) //Zjistí, jestli soubor [tabulka] již existuje a podle toho se zavolá pøíslušná metoda
	{
		table = this->createTable(name, fieldsCount, fields);
	}
	else
	{
		table = this->openTable(name);
	}

	return table;
}