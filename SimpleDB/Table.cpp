#include "dbapi.h"
#include "MyIterator.h"

// Vložení nového øádku do tabulky (pole Object* (pro jednotlivé hodnoty sloupeèkù))
void Table::insert(Object** row)
{
	data.push_back(row);
	rowCount++;
}
// Smazání vyrabného øádku z tabulky
void Table::remove(int rowid)
{
	data.erase(data.begin() + rowid);
	rowCount--;
}

// Select – vytvoøí iterátor k procházení tabulky
Iterator* Table::select()
{ 
	return new MyIterator(data); 
}

// Commit – pøenese zmìny z pamìti do datových souborù
void Table::commit()
{
	std::ofstream ofs(tableFilePath, std::ifstream::trunc);

	ofs << tableFieldsCount << std::endl;
	for (int i = 0; i < tableFieldsCount; i++)
	{
		ofs << tableFields[i]->getName() << ";" << std::to_string((int)tableFields[i]->getType()) << std::endl;
	} //Zapiš hlavièku

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
	} //Zapiš data
	ofs.close();
}

// Uzavøe tabulku (dealokuje pamìové prostøedky)
void Table::close()
{
	data.clear();
	data.shrink_to_fit();
}
