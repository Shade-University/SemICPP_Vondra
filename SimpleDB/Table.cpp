#include "dbapi.h"

// Vlo�en� nov�ho ��dku do tabulky (pole Object* (pro jednotliv� hodnoty sloupe�k�))
void Table::insert(Object** row)
{}
// Smaz�n� vyrabn�ho ��dku z tabulky
void Table::remove(int rowid){}

// Select � vytvo�� iter�tor k proch�zen� tabulky
Iterator* Table::select() { return nullptr; }

// Commit � p�enese zm�ny z pam�ti do datov�ch soubor�
void Table::commit(){}

// Uzav�e tabulku (dealokuje pam�ov� prost�edky)
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
