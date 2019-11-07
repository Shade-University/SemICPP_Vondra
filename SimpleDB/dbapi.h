#ifndef DBAPI_H
#define DBAPI_H

#ifdef DLL_SPEC_EXPORTS
#define DLL_SPEC __declspec(dllexport)
#else
#define DLL_SPEC __declspec(dllimport)
#endif
#include <functional>
#include <windows.h>
#include <stdio.h>
#include <string> 
#include <iostream>
#include <fstream>


class DLL_SPEC Object;
class DLL_SPEC Table;
class DLL_SPEC Db;

// Typ datov�ho pole
enum struct FieldType {
	Integer,
	Double,
	String,
	Field
};
// Polymorfn� datov� objekt (reprezentuje jednu datovou hodnotu v tabulce)
// Rozhran� vyhovuje z�kladn�m typ�m int, double, string; pro typ �field� je rozhran� roz���eno
class DLL_SPEC Object {
public:
	Object();
	virtual ~Object();

	// Gettery a settery podle typu
	// Jejich funkce je definov�na jen v p��pad�, �e aktu�ln� objekt je odpov�daj�c�ho typu
	// Automatick� konverze v z�kladn�m API nejsou vy�adov�ny

	virtual std::string getString() const;
	virtual void setString(std::string value);

	virtual int getInt() const;
	virtual void setInt(int value);

	virtual double getDouble() const;
	virtual void setDouble(double value);

	// Vrac� true, pokud aktu�ln� objekt p�edstavuje dan� typ
	virtual bool isType(FieldType type) const;
};


class DLL_SPEC IntObject : public Object {
public:
	IntObject() : value(0) {}
	IntObject(int v) : value(v) {}
private:
	int value;
};

class DLL_SPEC DoubleObject : public Object {
public:
	DoubleObject() : value(0.0) {}
	DoubleObject(double v) : value(v) {}
private:
	double value;
};

class DLL_SPEC StringObject : public Object {
public:
	StringObject() : value("") {}
	StringObject(std::string v) : value(v) {}
private:
	std::string value;
};

// Objekt popisuj�c� sloupe�ek �field�
class DLL_SPEC FieldObject : public Object {
public:
	FieldObject() {}
	FieldObject(std::string name, FieldType type) :name(name), type(type) {}

	virtual bool isType(FieldType type) const override
	{
		return false;
	}

	// N�zev sloupe�ku
	std::string getName() const { return name; }
	// Typ sloupe�ku
	FieldType getType() const { return type; }
private:
	std::string name;
	FieldType type;
};

class DLL_SPEC Db {
public:
	// Otev�e datab�zi
	static Db* open(std::string database);
	// Uzav�e datab�zi (dealokuje pam�ov� prost�edky)
	void close();

	// Vytvo�� novou tabulku
	Table* createTable(std::string name, int fieldsCount, FieldObject** fields);
	// Otev�e existuj�c� tabulku
	Table* openTable(std::string name);
	// Otev�e tabulku (pokud neexistuje, vytvo�� automaticky novou)
	Table* openOrCreateTable(std::string name, int fieldsCount, FieldObject** fields);

	// Alokuje objekt �int�
	static Object* Int(int value) { return new IntObject(value); }
	// Alokuje objekt �double�
	static Object* Double(double value) { return new DoubleObject(value); }
	// Alokuje objekt �string�
	static Object* String(std::string value) { return new StringObject(value); }
	// Alokuje objekt �field�
	static FieldObject* Field(std::string name, FieldType type) { return new FieldObject(name, type); }
private:	
	std::string databaseName;
	static std::string dbLocation;
};
// --------------------------------------------------------

// Rozhran� iter�toru (select)
class DLL_SPEC Iterator {
public:
	virtual ~Iterator() {}

	// Posun na dal�� ��dek (vrac� true, pokud je iter�tor platn�; logika podle Java Iterator)
	virtual bool moveNext() = 0;
	// Vrac� pole Object* obsahuj�c� data ��dku
	virtual Object** getRow() = 0;
	// Vrac� intern� rowId aktu�ln�ho ��dku
	virtual int getRowId() = 0;
	// Uzav�e iter�tor (dealokuje pam�ov� prost�edky)
	virtual void close() = 0;
};

// Tabulka
class DLL_SPEC Table {
public:
	Table(FieldObject** tableFields, int tableFieldsCount)
	{
		this->tableFields = tableFields;
		this->tableFieldsCount = tableFieldsCount;
		this->rowCount = 0;
	}
	// Vlo�en� nov�ho ��dku do tabulky (pole Object* (pro jednotliv� hodnoty sloupe�k�))
	void insert(Object** row);
	// Smaz�n� vyrabn�ho ��dku z tabulky
	void remove(int rowid);

	// Select � vytvo�� iter�tor k proch�zen� tabulky
	Iterator* select();

	// Commit � p�enese zm�ny z pam�ti do datov�ch soubor�
	void commit();

	// Uzav�e tabulku (dealokuje pam�ov� prost�edky)
	void close();

	// Vrac� po�et ��dk� v tabulce
	int getRowCount() const { return 0; }

	// Vrac� pole FieldObject* popisuj�c� sloupe�ky tabulky
	FieldObject** getFields() const { return tableFields; }

	// Vrac� po�et sloupe�k�
	int getFieldCount() const { return tableFieldsCount; }
private:
	int rowCount;
	int tableFieldsCount;
	FieldObject** tableFields;
	
};
#endif

