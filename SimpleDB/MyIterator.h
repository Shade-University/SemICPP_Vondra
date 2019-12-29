#pragma once
#include "dbapi.h"

class MyIterator : public Iterator {
public:
	MyIterator(std::vector<Object**> data) { this->data = data; currentRow = 0; } //Iter�tor z vectoru, kter� v sob� m� ��dky objekt�
	~MyIterator() { this->close(); } //P�i desktrutoru dealokuj pam�

	// Posun na dal�� ��dek (vrac� true, pokud je iter�tor platn�; logika podle Java Iterator)
	bool moveNext();
	// Vrac� pole Object* obsahuj�c� data ��dku
	Object** getRow();
	// Vrac� intern� rowId aktu�ln�ho ��dku
	int getRowId();
	// Uzav�e iter�tor (dealokuje pam�ov� prost�edky)
	void close();
private:
	std::vector<Object**> data;
	int currentRow;
};
