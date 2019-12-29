#pragma once
#include "dbapi.h"
#include "helpful.h"

class TableMenu
{
public:
	TableMenu(Table* table) { this->table = table; }

	//Otevøe menu tabulky
	void showTableMenuDialog();
private:
	Table* table;
	
	//Otevøe dialog pro insert do tabulky
	void insertToTableDialog();

	//Otevøe dialog pro remove z tabulky
	void removeFromTableDialog();

	//Zobrazí data v tabulce
	void showTableDialog();

	//Commitne zmìny
	void commitTableDialog();
};

