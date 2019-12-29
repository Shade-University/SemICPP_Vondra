#include "dbapi.h"
#include "MyIterator.h"

// Vlo�en� nov�ho ��dku do tabulky (pole Object* (pro jednotliv� hodnoty sloupe�k�))
void Table::insert(Object** row)
{
	data.push_back(row);
	rowCount++;
}
// Smaz�n� vyrabn�ho ��dku z tabulky
void Table::remove(int rowid)
{
	data.erase(data.begin() + rowid);
	rowCount--;
}

// Select � vytvo�� iter�tor k proch�zen� tabulky
Iterator* Table::select()
{ 
	return new MyIterator(data); 
}

// Commit � p�enese zm�ny z pam�ti do datov�ch soubor�
void Table::commit()
{
	std::ofstream ofs(tableFilePath, std::ifstream::trunc);

	ofs << tableFieldsCount << std::endl;
	for (int i = 0; i < tableFieldsCount; i++)
	{
		ofs << tableFields[i]->getName() << ";" << std::to_string((int)tableFields[i]->getType()) << std::endl;
	} //Zapi� hlavi�ku

	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < tableFieldsCount; j++)
		{
			switch (tableFields[j]->getType())
			{
			case FieldType::String: ofs << data.at(i)[j]->getString() << ";"; break;
			case FieldType::Integer: ofs << data.at(i)[j]->getInt() << ";"; break;
			case FieldType::Double: ofs << data.at(i)[j]->getDouble() << ";"; break;
			}
		}
		ofs << std::endl;
	} //Zapi� data
	ofs.close();
}

// Uzav�e tabulku (dealokuje pam�ov� prost�edky)
void Table::close()
{
	data.clear();
	data.shrink_to_fit();
}
