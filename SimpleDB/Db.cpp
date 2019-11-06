#include "dbapi.h"

// Otevøe databázi
Db* Db::open(std::string database)
{
	std::cout << "Hello" << std::endl;
	return nullptr;
}

// Vytvoøí novou tabulku
Table* Db::createTable(std::string name, int fieldsCount, FieldObject** fields)
{
	return nullptr;
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