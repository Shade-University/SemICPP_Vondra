#pragma once
#include "dbapi.h"
class DbMenu
{
private:
	Db* db;
public:
	//Otevøe dialog pro zvolení DB (Pokud existuje otevøe, pokud neexistuje vytvoøí)
	static Db* connectDbDialog();
	
	DbMenu(Db* db) { this->db = db; }

	//Dialog pro vytvoøení tabulky
	void createTableDialog();

	//Dialog pro otevøení tabulky. Otevøe dialog s menu pro danou tabulku
	void openTableDialog();

};

