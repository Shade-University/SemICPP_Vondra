#include "dbapi.h"


Object::Object()
{}
Object::~Object()
{}

// Gettery a settery podle typu
// Jejich funkce je definována jen v pøípadì, že aktuální objekt je odpovídajícího typu
// Automatické konverze v základním API nejsou vyžadovány

std::string Object::getString() const
{
	return nullptr;
}
void Object::setString(std::string value)
{}

int Object::getInt() const
{
	return 0;
}
void Object::setInt(int value)
{}

double Object::getDouble() const
{
	return 0;
}
void Object::setDouble(double value)
{}

// Vrací true, pokud aktuální objekt pøedstavuje daný typ
bool Object::isType(FieldType type) const
{
	return NULL;
}