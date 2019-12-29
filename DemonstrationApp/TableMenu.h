#pragma once
#include "dbapi.h"
#include "helpful.h"

class TableMenu
{
public:
	TableMenu(Table* table) { this->table = table; }
	void showTableMenuDialog();
private:
	Table* table;
	void insertToTableDialog();
	void removeFromTableDialog();
	void showTableDialog();
	void commitTableDialog();

	std::string getTypeName(FieldObject* fieldObject);
};

