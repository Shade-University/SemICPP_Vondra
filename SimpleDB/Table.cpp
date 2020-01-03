#include "dbapi.h"
#include "MyIterator.h"

void Table::insert(Object** row)
{
	data.push_back(row);
	rowCount++;
} //Insert do vectoru

void Table::remove(int rowid)
{
	Object** row = data.at(rowid);
	data.erase(data.begin() + rowid); //Odstran�n� z vectoru

	for (int i = 0; i < tableFieldsCount; i++)
	{
		delete row[i];
	}
	delete[] row; //dealokace

	rowCount--;
} //Vymaz�n� z vektoru

Iterator* Table::select()
{ 
	return new MyIterator(data); 
} //Vr�cen� vlastn�ho iter�toru

void Table::commit()
{
	std::ofstream ofs(tableFilePath, std::ifstream::trunc); //trunc p�ema�e minul� soubor

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
	} //Zapi� data podle typu typu sloupce
	ofs.close();
}

void Table::close()
{
	for (int i = 0; i < data.size(); ++i) {
		for (int j = 0; j < tableFieldsCount; j++)
		{
			delete data[i][j];
		} //Dealokuj objekty v ��dc�ch
		delete[] data[i]; //dealokuj ��dky
	}

	data.clear();
	data.shrink_to_fit();
} //Vy�isti pam� vectoru
