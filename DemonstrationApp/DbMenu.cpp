
#include "DbMenu.h"
#include "TableMenu.h"

Db* DbMenu::connectDbDialog()
{
	Db* db;
	std::cout << "Testovni aplikace pro Icpp1 - Databaze se studenty a jejich predmety" << std::endl;
	std::cout << "====================================================================" << std::endl;
	std::cout << std::endl;

	std::string dbName;
	std::cout << "Zadejte nazev databaze (SchoolDb obsahuje testovni data): ";
	std::cin >> dbName;

	db = Db::open(dbName);
	std::cout << "Databaze " << dbName << " pripojena" << std::endl;
	system("pause");

	return db;
}

void DbMenu::createTableDialog()
{
	std::cout << "Volba 1 - Vytvoreni tabulky" << std::endl;
	std::cout << "===========================" << std::endl;
	std::cout << std::endl;

	std::cout << "Zadejte nazev tabulky: ";
	std::string tableName;
	std::cin >> tableName;

	std::cout << "Zadejte pocet sloupcu: ";
	int fieldCount;
	std::cin >> fieldCount;
	std::cout << std::endl;

	FieldObject** fields = new FieldObject * [fieldCount];
	for (int i = 0; i < fieldCount; i++)
	{
		std::cout << "Sloupec " << i + 1 << std::endl;

		std::cout << "Nazev sloupce: ";
		std::string fieldName;
		std::cin >> fieldName;

		std::cout << "Datovy typ sloupce" << std::endl;
		std::cout << "1 - String" << std::endl;
		std::cout << "2 - Integer" << std::endl;
		std::cout << "3 - Double" << std::endl;

		std::cout << "Volba: ";
		int choice;
		std::cin >> choice;

		FieldType fieldType;
		switch (choice)
		{
		case 1:
			fieldType = FieldType::String;
			break;
		case 2:
			fieldType = FieldType::Integer;
			break;
		case 3:
			fieldType = FieldType::Double;
			break;
		}
		fields[i] = Db::Field(fieldName, fieldType);
	}

	Table* table = db->createTable(tableName, fieldCount, fields);
	std::cout << "Tabulka zalozena" << std::endl;
	system("pause");
}

void DbMenu::openTableDialog()
{
	std::cout << "Volba 2 - Otevreni tabulky" << std::endl;
	std::cout << "===========================" << std::endl;
	std::cout << std::endl;

	std::cout << "Zadejte nazev tabulky: ";
	std::string tableName;
	std::cin >> tableName;

	Table* table = db->openTable(tableName);
	TableMenu* tableMenu = new TableMenu(table);
	
	tableMenu->showTableMenuDialog();
}