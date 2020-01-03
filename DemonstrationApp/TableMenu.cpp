#include "TableMenu.h"

void TableMenu::showTableMenuDialog()
{
	bool repeat = true;

	while (repeat)
	{
		system("cls");
		std::cout << "Menu tabulky: " << std::endl;
		std::cout << "==============" << std::endl;
		std::cout << std::endl;

		std::cout << "1 - Vlozit radek" << std::endl;
		std::cout << "2 - Odstranit radek" << std::endl;
		std::cout << "3 - Zobrazit data" << std::endl;
		std::cout << "4 - Commit" << std::endl;
		std::cout << "5 - Zpet" << std::endl;



		std::cout << std::endl;
		std::cout << "Zadejte volbu: ";
		int choice;
		std::cin >> choice;
		std::cout << std::endl;
		std::cout << std::endl;

		switch (choice)
		{
		case 1:
			insertToTableDialog();
			break;
		case 2:
			removeFromTableDialog();
			break;
		case 3:
			showTableDialog();
			break;
		case 4:
			commitTableDialog();
			break;
		case 5:
			repeat = false;
			break;
		}
	}
}

void TableMenu::insertToTableDialog()
{
	std::cout << "Volba 1 - Vlozit radek" << std::endl;
	std::cout << "======================" << std::endl;
	std::cout << std::endl;

	Object** rowsValues = new Object *[table->getFieldCount()];
	for (int i = 0; i < table->getFieldCount(); i++)
	{
		FieldObject* field = table->getFields()[i];
		std::cout << "Sloupec " << field->getName();

		Object* valueObject = nullptr;{}
		if (field->getType() == FieldType::Integer)
		{
			std::cout << ", Typ Integer" << std::endl;
			int intValue;
			std::cout << "Zadejte hodnotu integer: ";
			std::cin >> intValue;
			valueObject = Db::Int(intValue);
		} 
		else if (field->getType() == FieldType::String)
		{
			std::cout << ", Typ String" << std::endl;
			std::string stringValue;
			std::cout << "Zadejte hodnotu string: ";
			std::cin >> stringValue;
			valueObject = Db::String(stringValue);
		}
		else if (field->getType() == FieldType::Double)
		{
			std::cout << ", Typ Double" << std::endl;
			double value;
			std::cout << "Zadejte hodnotu double (oddelovac .): ";
			std::cin >> value;
			valueObject = Db::Double(value);
		}
		rowsValues[i] = valueObject;
	}

	table->insert(rowsValues);
	std::cout << "Radek vlozen" << std::endl;
	system("pause");
}

void TableMenu::removeFromTableDialog()
{
	std::cout << "Volba 2 - Odstranit radek" << std::endl;
	std::cout << "=========================" << std::endl;
	std::cout << std::endl;

	std::cout << "Zadejte cislo radku(0 - " << table->getRowCount() << "): ";
	int rowNumber;
	std::cin >> rowNumber;

	table->remove(rowNumber);
	std::cout << "Radek odstranen" << std::endl;
	system("pause");
}

void TableMenu::showTableDialog()
{
	std::cout << "Volba 3 - Zobrazit data" << std::endl;
	std::cout << "=======================" << std::endl;
	std::cout << std::endl;

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

	system("pause");
}

void TableMenu::commitTableDialog()
{
	std::cout << "Volba 4 - Commit" << std::endl;
	std::cout << "=======================" << std::endl;
	std::cout << std::endl;

	table->commit();
	std::cout << "Commit byl proveden" << std::endl;
	system("pause");
}