#include "RelationTable.h"

RelationTable::RelationTable(Table* table1, Table* table2, int firstColumn, int secondColumn)
{
	this->mainTable = table1;
	this->secondTable = table2;
	this->foreignKeyColumnNumber = firstColumn;
	this->targetColumnNumber = secondColumn;

}

void RelationTable::show()
{
	Iterator* iterMain = mainTable->select();

	while (iterMain->moveNext())
	{
		Object** row = iterMain->getRow();
		std::cout << "|";
		for (int i = 0; i < mainTable->getFieldCount(); i++)
		{
			if (row[i]->isType(FieldType::String))
				std::cout << row[i]->getString();
			else if (row[i]->isType(FieldType::Integer))
				std::cout << row[i]->getInt();
			else if (row[i]->isType(FieldType::Double))
				std::cout << row[i]->getDouble();

			std::cout << "|";

			if (foreignKeyColumnNumber - 1 == i)
			{
				Iterator* iterTarget = secondTable->select();
				while (iterTarget->moveNext())
				{
					Object** row2 = iterTarget->getRow();
					if (row[i]->getInt() == row2[targetColumnNumber - 1]->getInt())
					{
						for (int j = 0; j < secondTable->getFieldCount(); j++)
						{
							if (row2[j]->isType(FieldType::String))
								std::cout << row2[j]->getString();
							else if (row2[j]->isType(FieldType::Integer))
								std::cout << row2[j]->getInt();
							else if (row2[j]->isType(FieldType::Double))
								std::cout << row2[j]->getDouble();
							std::cout << "|";
						}
					}
				}
			}
		}
		std::cout << std::endl;
	}
}