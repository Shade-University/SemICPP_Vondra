#include "dbapi.h"
#include "helpful.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
	// Vytvo�en�/otev�en� db
	Db* db = Db::open("testdb");
	// Vytvo�en�/otev�en� tabulky
	/*auto idField = Db::Field("id", FieldType::Integer);
	auto nameField = Db::Field("name", FieldType::String);
	auto userFields = combineToDefinition(idField, nameField);
	Table* users = db->openOrCreateTable("users", 2, userFields);
	// Vlo�en� ��dku do tabulky
	auto id = Db::Int(15);
	auto name = Db::String("Peter");
	auto row = combineToRow(id, name);
	users->insert(row);
	// Select
	auto it = users->select();
	while (it->moveNext())
	{
		auto row = it->getRow();
		cout << row[0]->getInt() << ": " << row[1]->getString() << endl;
	}
	it->close();
	// Ulo�en� tabulky na disk
	users->commit();
	// Uzav�en� tabulky (a dealokace pam�ov�ch prost�edk�)
	users->close();
	// Uzav�en� db (a dealokace pam�ov�ch prost�edk�)
	db->close();*/

	std::cin.get();
	return 0;
}
