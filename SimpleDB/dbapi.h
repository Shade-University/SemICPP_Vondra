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

// Typ datového pole
enum struct FieldType {
	Integer,
	Double,
	String,
	Field
};
// Polymorfní datovı objekt (reprezentuje jednu datovou hodnotu v tabulce)
// Rozhraní vyhovuje základním typùm int, double, string; pro typ „field“ je rozhraní rozšíøeno
class DLL_SPEC Object {
public:
	Object();
	virtual ~Object();

	// Gettery a settery podle typu
	// Jejich funkce je definována jen v pøípadì, e aktuální objekt je odpovídajícího typu
	// Automatické konverze v základním API nejsou vyadovány

	virtual std::string getString() const;
	virtual void setString(std::string value);

	virtual int getInt() const;
	virtual void setInt(int value);

	virtual double getDouble() const;
	virtual void setDouble(double value);

	// Vrací true, pokud aktuální objekt pøedstavuje danı typ
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

// Objekt popisující sloupeèek „field“
class DLL_SPEC FieldObject : public Object {
public:
	FieldObject() {}
	FieldObject(std::string name, FieldType type) :name(name), type(type) {}

	virtual bool isType(FieldType type) const override
	{
		return false;
	}

	// Název sloupeèku
	std::string getName() const { return name; }
	// Typ sloupeèku
	FieldType getType() const { return type; }
private:
	std::string name;
	FieldType type;
};

class DLL_SPEC Db {
public:
	// Otevøe databázi
	static Db* open(std::string database);
	// Uzavøe databázi (dealokuje pamìové prostøedky)
	void close();

	// Vytvoøí novou tabulku
	Table* createTable(std::string name, int fieldsCount, FieldObject** fields);
	// Otevøe existující tabulku
	Table* openTable(std::string name);
	// Otevøe tabulku (pokud neexistuje, vytvoøí automaticky novou)
	Table* openOrCreateTable(std::string name, int fieldsCount, FieldObject** fields);

	// Alokuje objekt „int“
	static Object* Int(int value) { return new IntObject(value); }
	// Alokuje objekt „double“
	static Object* Double(double value) { return new DoubleObject(value); }
	// Alokuje objekt „string“
	static Object* String(std::string value) { return new StringObject(value); }
	// Alokuje objekt „field“
	static FieldObject* Field(std::string name, FieldType type) { return new FieldObject(name, type); }
private:	
	std::string databaseName;
	static std::string dbLocation;
};
// --------------------------------------------------------

// Rozhraní iterátoru (select)
class DLL_SPEC Iterator {
public:
	virtual ~Iterator() {}

	// Posun na další øádek (vrací true, pokud je iterátor platnı; logika podle Java Iterator)
	virtual bool moveNext() = 0;
	// Vrací pole Object* obsahující data øádku
	virtual Object** getRow() = 0;
	// Vrací interní rowId aktuálního øádku
	virtual int getRowId() = 0;
	// Uzavøe iterátor (dealokuje pamìové prostøedky)
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
	// Vloení nového øádku do tabulky (pole Object* (pro jednotlivé hodnoty sloupeèkù))
	void insert(Object** row);
	// Smazání vyrabného øádku z tabulky
	void remove(int rowid);

	// Select – vytvoøí iterátor k procházení tabulky
	Iterator* select();

	// Commit – pøenese zmìny z pamìti do datovıch souborù
	void commit();

	// Uzavøe tabulku (dealokuje pamìové prostøedky)
	void close();

	// Vrací poèet øádkù v tabulce
	int getRowCount() const { return 0; }

	// Vrací pole FieldObject* popisující sloupeèky tabulky
	FieldObject** getFields() const { return tableFields; }

	// Vrací poèet sloupeèkù
	int getFieldCount() const { return tableFieldsCount; }
private:
	int rowCount;
	int tableFieldsCount;
	FieldObject** tableFields;
	
};
#endif

