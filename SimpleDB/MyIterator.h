#pragma once
#include "dbapi.h"

class MyIterator : public Iterator {
public:
	MyIterator(std::vector<Object**> data) { this->data = data; currentRow = 0; } //Iterátor z vectoru, kterı v sobì má øádky objektù
	~MyIterator() { this->close(); } //Pøi desktrutoru dealokuj pamì

	// Posun na další øádek (vrací true, pokud je iterátor platnı; logika podle Java Iterator)
	bool moveNext();
	// Vrací pole Object* obsahující data øádku
	Object** getRow();
	// Vrací interní rowId aktuálního øádku
	int getRowId();
	// Uzavøe iterátor (dealokuje pamìové prostøedky)
	void close();
private:
	std::vector<Object**> data;
	int currentRow;
};
