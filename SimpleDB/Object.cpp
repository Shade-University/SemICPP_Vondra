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
	if (dynamic_cast<const StringObject*>(this) == nullptr)
		throw std::runtime_error("Bad object type for method getString");

	StringObject* stringObject = (StringObject*)this;
	return stringObject->getValue();
}
void Object::setString(std::string value)
{
	if (dynamic_cast<const StringObject*>(this) == nullptr)
		throw std::runtime_error("Bad object type for method setString");

	StringObject* stringObject = (StringObject*)this;
	stringObject->setValue(value);
}

int Object::getInt() const
{
	if (dynamic_cast<const IntObject*>(this) == nullptr)
		throw std::runtime_error("Bad object type for method getInt");

	IntObject* intObject = (IntObject*)this;
	return intObject->getValue();
}
void Object::setInt(int value)
{
	if (dynamic_cast<const IntObject*>(this) == nullptr)
		throw std::runtime_error("Bad object type for method setInt");

	IntObject* intObject = (IntObject*)this;
	intObject->setValue(value);
}

double Object::getDouble() const
{
	if (dynamic_cast<const DoubleObject*>(this) == nullptr)
		throw std::runtime_error("Bad object type for method setDouble");

	DoubleObject* doubleObject = (DoubleObject*)this;
	return doubleObject->getValue();
}
void Object::setDouble(double value)
{
	if (dynamic_cast<const DoubleObject*>(this) == nullptr)
		throw std::runtime_error("Bad object type for method setDouble");

	DoubleObject* doubleObject = (DoubleObject*)this;
	doubleObject->setValue(value);
}

// Vrac� true, pokud aktu�ln� objekt p�edstavuje dan� typ
bool Object::isType(FieldType type) const
{
	switch (type)
	{
	case FieldType::String:
		return dynamic_cast<const StringObject*>(this) != nullptr;
		break;
	case FieldType::Integer:
		return dynamic_cast<const IntObject*>(this) != nullptr;
		break;
	case FieldType::Double:
		return dynamic_cast<const DoubleObject*>(this) != nullptr;
		break;
	default:
		return false;
	}
}