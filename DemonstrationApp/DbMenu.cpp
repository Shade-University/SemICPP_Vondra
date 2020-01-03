
#include "DbMenu.h"

Db* DbMenu::connectDbDialog()
{
	Db* db;
	std::cout << "Testovni aplikace pro Icpp1" << std::endl;
	std::cout << "===========================" << std::endl;
	std::cout << std::endl;

	std::string dbName;
	std::cout << "Zadejte nazev databaze (SchoolDb obsahuje testovni data): ";
	std::cin >> dbName;

	db = Db::open(dbName);
	std::cout << std::endl << "Databaze " << dbName << " pripojena" << std::endl << std::endl;
	system("pause");

	return db;
}

Table* DbMenu::createTableDialog()
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

	FieldObject** fields = new FieldObject *[fieldCount];
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

		FieldType fieldType{};
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
	return table;
}

void DbMenu::openTableDialog()
{
	std::cout << "Volba 2 - Otevreni tabulky" << std::endl;
	std::cout << "===========================" << std::endl;
	std::cout << std::endl;

	std::vector<Table*> loadedTables = loadTables(db);
	for (int i = 0; i < loadedTables.size(); i++)
	{
		std::cout << loadedTables[i]->getTableName() << std::endl;
	} //Zobraz tabulky

	std::cout << std::endl << "Zadejte nazev tabulky: ";
	std::string tableName;
	std::cin >> tableName;

	Table* table = db->openTable(tableName);
	TableMenu tableMenu(table);

	tableMenu.showTableMenuDialog();
}

void DbMenu::createMenuConnectTablesDialog()
{
	std::vector<Table*> tables;
	std::cout << "Volba 3 - Menu spojovani tabulek" << std::endl;
	std::cout << "================================" << std::endl;
	std::cout << std::endl;

	std::cout << "Databaze: " << db->getDatabaseName() << std::endl;
	std::cout << "Tabulky: " << std::endl;
	tables = loadTables(db);
	RelationTable* relationTable = loadRelationTable(tables);
	relationTables.push_back(relationTable);

	std::cout << "Tabulky propojeny" << std::endl;
	system("pause");
}
std::vector<Table*> DbMenu::loadTables(Db* db)
{
	std::vector<Table*> tables;
	std::string path = db->dbLocation + db->getDatabaseName();

	int i = 0;
	for (const auto& entry : std::filesystem::directory_iterator(path)) //Získej všechny soubory (tabulky) z databázové složky
	{
		std::string name = entry.path().string();
		int pathPosition = name.find_last_of("\\") + 1;
		int extensionPosition = name.find_last_of(".");

		std::string rawname = name.substr(pathPosition, extensionPosition - pathPosition); //Získej název tabulky ze souboru

		std::cout << ++i << " - " << rawname << std::endl;
		tables.push_back(db->openTable(rawname)); //Naèti tabulky do pamìti
	}
	return tables;
}

void DbMenu::showTableColumns(Table* table)
{
	Iterator* iter = table->select();
	while (iter->moveNext())
	{
		Object** row = iter->getRow();
		std::cout << "|";
		for (int i = 0; i < table->getFieldCount(); i++)
		{
			if (row[i]->isType(FieldType::String))
				std::cout << row[i]->getString();
			else if (row[i]->isType(FieldType::Integer))
				std::cout << row[i]->getInt();
			else if (row[i]->isType(FieldType::Double))
				std::cout << row[i]->getDouble();

			std::cout << "\t|";
		}
		std::cout << std::endl;
	}
	iter->close();
}

RelationTable* DbMenu::loadRelationTable(std::vector<Table*> tables)
{
	Table* table1;
	Table* table2;
	std::cout << std::endl << "Zadejte tabulku kterou chcete propojit relaci: ";
	int table1Column;
	std::cin >> table1Column;
	table1 = tables.at(table1Column - 1);
	showTableColumns(table1);

	std::cout << std::endl << "Zadejte kolikaty sloupec by mel byt cizi klic (prozatim funguje pouze pro typ int): ";
	int foreigKeyColumn;
	std::cin >> foreigKeyColumn;

	std::cout << std::endl << "Zadejte druhou tabulku kterou chcete propojit relaci: ";
	int table2Column;
	std::cin >> table2Column;
	table2 = tables.at(table2Column - 1);
	showTableColumns(table2);

	std::cout << std::endl << "Zadejte kolikaty sloupec by se mel propojit s cizim klicem (stejny typ jako cizi klic, pouze int): ";
	int targetColumn;
	std::cin >> targetColumn;

	return new RelationTable(table1, table2, foreigKeyColumn, targetColumn);
}

void DbMenu::showConnectedTables()
{
	for (int i = 0; i < relationTables.size(); i++)
	{
		relationTables.at(i)->show();
		std::cout << std::endl;
		system("pause");
	}
}



