#pragma once
#include "dbapi.h"
class DbMenu
{
private:
	Db* db;
public:
	static Db* connectDbDialog();
	
	DbMenu(Db* db) { this->db = db; }
	void createTableDialog();
	void openTableDialog();

};

