#pragma once
#include "dbapi.h"
#include <filesystem>
#include "RelationTable.h"
#include "TableMenu.h"

class DbMenu
{
private:
	Db* db;
	std::vector<RelationTable*> relationTables;
	void showTableColumns(Table* table);
	std::vector<Table*> loadTables(Db* db);
	RelationTable* loadRelationTable(std::vector<Table*> tables);
public:
	//Otevøe dialog pro zvolení DB (Pokud existuje otevøe, pokud neexistuje vytvoøí)
	static Db* connectDbDialog();
	
	DbMenu(Db* db) { this->db = db; }

	//Dialog pro vytvoøení tabulky
	Table* createTableDialog();

	//Dialog pro otevøení tabulky. Otevøe dialog s menu pro danou tabulku
	void openTableDialog();

	void createMenuConnectTablesDialog();

	void showConnectedTables();


};

