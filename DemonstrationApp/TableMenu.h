#pragma once
#include "dbapi.h"
#include "helpful.h"

class TableMenu
{
public:
	TableMenu(Table* table) { this->table = table; }

	//Otev�e menu tabulky
	void showTableMenuDialog();
private:
	Table* table;
	
	//Otev�e dialog pro insert do tabulky
	void insertToTableDialog();

	//Otev�e dialog pro remove z tabulky
	void removeFromTableDialog();

	//Zobraz� data v tabulce
	void showTableDialog();

	//Commitne zm�ny
	void commitTableDialog();
};

