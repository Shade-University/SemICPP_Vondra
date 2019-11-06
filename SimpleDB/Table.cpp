#include "dbapi.h"

// Vloení nového øádku do tabulky (pole Object* (pro jednotlivé hodnoty sloupeèkù))
void Table::insert(Object** row)
{}
// Smazání vyrabného øádku z tabulky
void Table::remove(int rowid){}

// Select – vytvoøí iterátor k procházení tabulky
Iterator* Table::select() { return nullptr; }

// Commit – pøenese zmìny z pamìti do datovıch souborù
void Table::commit(){}

// Uzavøe tabulku (dealokuje pamìové prostøedky)
void Table::close(){}

int Table::getRowCount() const
{
	return 0;
}

FieldObject** Table::getFields() const
{
	return nullptr;
}

int Table::getFieldCount() const
{
	return 0;
}
