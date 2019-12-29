#pragma once
#include "dbapi.h"
class DbMenu
{
private:
	Db* db;
public:
	//Otev�e dialog pro zvolen� DB (Pokud existuje otev�e, pokud neexistuje vytvo��)
	static Db* connectDbDialog();
	
	DbMenu(Db* db) { this->db = db; }

	//Dialog pro vytvo�en� tabulky
	void createTableDialog();

	//Dialog pro otev�en� tabulky. Otev�e dialog s menu pro danou tabulku
	void openTableDialog();

};

