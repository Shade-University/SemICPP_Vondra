#include "dbapi.h"


Object::Object()
{}
Object::~Object()
{}

// Gettery a settery podle typu
// Jejich funkce je definov�na jen v p��pad�, �e aktu�ln� objekt je odpov�daj�c�ho typu
// Automatick� konverze v z�kladn�m API nejsou vy�adov�ny

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

// Vrac� true, pokud aktu�ln� objekt p�edstavuje dan� typ
bool Object::isType(FieldType type) const
{
	return NULL;
}