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
	//Otev�e dialog pro zvolen� DB (Pokud existuje otev�e, pokud neexistuje vytvo��)
	static Db* connectDbDialog();
	
	DbMenu(Db* db) { this->db = db; }
	~DbMenu() {
		for (int i = 0; i < relationTables.size(); i++)
		{
			delete relationTables[i];
		}
		relationTables.clear();
		relationTables.shrink_to_fit();
	}

	//Dialog pro vytvo�en� tabulky
	Table* createTableDialog();

	//Dialog pro otev�en� tabulky. Otev�e dialog s menu pro danou tabulku
	void openTableDialog();

	//Dialog pro propojen� tabulek do relace
	void createMenuConnectTablesDialog();

	//Zobraz� propojen� tabulky
	void showConnectedTables();


};

