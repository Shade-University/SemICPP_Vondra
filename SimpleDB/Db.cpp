#include "dbapi.h"

std::string Db::dbLocation = "databases/";
// Otev�e datab�zi
Db* Db::open(std::string database)
{
	std::string path = dbLocation + database;
	CreateDirectory(path.c_str(), NULL);
	Db* db = new Db();
	db->databaseName = database;
	return db;
}

// Vytvo�� novou tabulku
Table* Db::createTable(std::string name, int fieldsCount, FieldObject** fields)
{
	//TODO Stejn� tabulka ?
	std::string file = dbLocation + databaseName + "/" + name + ".schema";
	std::ofstream ofs(file, std::ifstream::trunc);

	for (int i = 0; i < fieldsCount; i++)
	{
		ofs << fields[i]->getName() << ";" << std::to_string((int)fields[i]->getType()) << std::endl;
	}

	return new Table(fields, fieldsCount);
}
// Otev�e existuj�c� tabulku
Table* Db::openTable(std::string name)
{
	return nullptr;
}
// Otev�e tabulku (pokud neexistuje, vytvo�� automaticky novou)
Table* Db::openOrCreateTable(std::string name, int fieldsCount, FieldObject** fields)
{
	return nullptr;
}