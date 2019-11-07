#include "dbapi.h"

std::string Db::dbLocation = "databases/";
// Otevøe databázi
Db* Db::open(std::string database)
{
	std::string path = dbLocation + database;
	CreateDirectory(path.c_str(), NULL);
	Db* db = new Db();
	db->databaseName = database;
	return db;
}

// Vytvoøí novou tabulku
Table* Db::createTable(std::string name, int fieldsCount, FieldObject** fields)
{
	//TODO Stejná tabulka ?
	std::string file = dbLocation + databaseName + "/" + name + ".schema";
	std::ofstream ofs(file, std::ifstream::trunc);

	for (int i = 0; i < fieldsCount; i++)
	{
		ofs << fields[i]->getName() << ";" << std::to_string((int)fields[i]->getType()) << std::endl;
	}

	return new Table(fields, fieldsCount);
}
// Otevøe existující tabulku
Table* Db::openTable(std::string name)
{
	return nullptr;
}
// Otevøe tabulku (pokud neexistuje, vytvoøí automaticky novou)
Table* Db::openOrCreateTable(std::string name, int fieldsCount, FieldObject** fields)
{
	return nullptr;
}