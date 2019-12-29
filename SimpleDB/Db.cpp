#include "dbapi.h"

std::string Db::dbLocation = "databases/";
// Otevøe databázi
Db* Db::open(std::string database)
{
	std::string path = dbLocation + database;
	if (CreateDirectory(dbLocation.c_str(), NULL))
		printf("Directory with databases created\n");
	if (CreateDirectory(path.c_str(), NULL))
		printf("Database created\n");

	Db* db = new Db();
	db->databaseName = database;
	return db;
}

// Vytvoøí novou tabulku
Table* Db::createTable(std::string name, int fieldsCount, FieldObject** fields)
{
	std::string file = dbLocation + databaseName + "/" + name + ".schema";
	std::ofstream ofs(file, std::ifstream::trunc);

	ofs << fieldsCount << std::endl;
	for (int i = 0; i < fieldsCount; i++)
	{
		ofs << fields[i]->getName() << ";" << std::to_string((int)fields[i]->getType()) << std::endl;
	}

	return new Table(fields, fieldsCount, file);
}
// Otevøe existující tabulku
Table* Db::openTable(std::string name)
{
	int fieldsCount = 0;
	std::string file = dbLocation + databaseName + "/" + name + ".schema";
	std::ifstream ifile(file);
	ifile >> fieldsCount;



	FieldObject** fields = new FieldObject * [fieldsCount];
	std::string line;
	std::getline(ifile, line);
	for (int i = 0; i < fieldsCount; i++)
	{
		std::getline(ifile, line);
		int separatorPosition = line.find(';');
		std::string fieldName = line.substr(0, separatorPosition);
		int fieldType = std::stoi(line.substr(separatorPosition + 1, line.length()));
		FieldType type = static_cast<FieldType>(fieldType);

		FieldObject* fieldObject = new FieldObject(fieldName, type);
		fields[i] = fieldObject;
	}

	std::vector<Object**> data;
	std::vector<std::string> tokens;
	std::string word;
	while (std::getline(ifile, line))
	{
		std::stringstream s(line);

		while (std::getline(s, word, ';')) {
			tokens.push_back(word);
		}

		Object** row = new Object * [fieldsCount];
		for (int j = 0; j < fieldsCount; j++)
		{
			switch (fields[j]->getType())
			{
			case FieldType::String: row[j] = Db::String(tokens[j]); break;
			case FieldType::Integer: row[j] = Db::Int(std::stoi(tokens[j])); break;
			case FieldType::Double: row[j] = Db::Double(std::stod(tokens[j])); break;
			}
		}
		data.push_back(row);
	}

	return new Table(fields, fieldsCount, file, data);
}
// Otevøe tabulku (pokud neexistuje, vytvoøí automaticky novou)
Table* Db::openOrCreateTable(std::string name, int fieldsCount, FieldObject** fields)
{
	Table* table;
	std::string path = dbLocation + databaseName + "/" + name + ".schema";
	std::ifstream ifile(path);

	if (ifile.fail())
	{
		table = this->createTable(name, fieldsCount, fields);
	}
	else
	{
		table = this->openTable(name);
	}

	return table;
}