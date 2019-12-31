#pragma once
#include "dbapi.h"
#include <vector>
class RelationTable
{
private:
	Table* mainTable;
	int foreignKeyColumnNumber;
	Table* secondTable;
	int targetColumnNumber;

public:
	RelationTable(Table* table1, Table* table2, int firstColumn, int secondColumn);
	void show();
};

