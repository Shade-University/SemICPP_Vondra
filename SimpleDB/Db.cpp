#include "dbapi.h"

// Otev�e datab�zi
Db* Db::open(std::string database)
{
	std::cout << "Hello" << std::endl;
	return nullptr;
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