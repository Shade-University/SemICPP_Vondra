#include "dbapi.h"
#include <direct.h>

// Otev�e datab�zi
Db* Db::open(std::string database)
{
	std::string path = "databases/" + database;
	CreateDirectory(path.c_str(), NULL);
	Db* db = new Db();
	db->databaseName = database;
	return db;
}

// Vytvo�� novou tabulku
Table* Db::createTable(std::string name, int fieldsCount, FieldObject** fields)
{
	return nullptr;
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