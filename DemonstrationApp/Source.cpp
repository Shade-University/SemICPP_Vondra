#include "dbapi.h"
#include "helpful.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
	// Vytvoøení/otevøení db
	Db* db = Db::open("testdb");
	// Vytvoøení/otevøení tabulky
	/*auto idField = Db::Field("id", FieldType::Integer);
	auto nameField = Db::Field("name", FieldType::String);
	auto userFields = combineToDefinition(idField, nameField);
	Table* users = db->openOrCreateTable("users", 2, userFields);
	// Vložení øádku do tabulky
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
	// Uložení tabulky na disk
	users->commit();
	// Uzavøení tabulky (a dealokace pamìových prostøedkù)
	users->close();
	// Uzavøení db (a dealokace pamìových prostøedkù)
	db->close();*/

	std::cin.get();
	return 0;
}
