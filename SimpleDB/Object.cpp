#include "dbapi.h"


Object::Object()
{}
Object::~Object()
{}

std::string Object::getString() const
{
	if (dynamic_cast<const StringObject*>(this) == nullptr) //Pøetypuj na String objekt. Pokud se nepovede, vyhoï exception
		throw std::runtime_error("Bad object type for method getString");

	StringObject* stringObject = (StringObject*)this; //TODO mohl jsem pøetypovat u v dynamic_castu
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

// Vrací true, pokud aktuální objekt pøedstavuje danı typ
bool Object::isType(FieldType type) const
{
	switch (type)
	{
	case FieldType::String:
		return dynamic_cast<const StringObject*>(this) != nullptr; //Pokud se povede pøetypovat na danı objekt, vra true
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