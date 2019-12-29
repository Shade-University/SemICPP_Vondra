#include "dbapi.h"
#include "helpful.h"
#include "DbMenu.h"

void showMainDialog(DbMenu* dbMenu);

int main() {
	Db* db = DbMenu::connectDbDialog();
	DbMenu* dbMenu = new DbMenu(db);
	showMainDialog(dbMenu);
	
	//end
	db->close();
	std::cout << "Dekuji za vyzkouseni aplikace. Doufam, ze vse fungovalo jak melo. :)" << std::endl;
	std::cin.get(); std::cin.get();
}
void showMainDialog(DbMenu* dbMenu)
{
	bool repeat = true;

	while (repeat)
	{
		system("cls");
		std::cout << "Hlavni menu aplikace: " << std::endl;
		std::cout << "====================" << std::endl;
		std::cout << std::endl;

		std::cout << "1 - Vytvorit tabulku" << std::endl;
		std::cout << "2 - Otevrit tabulku" << std::endl;
		std::cout << "5 - Ukoncit aplikaci" << std::endl;

		std::cout << std::endl;
		std::cout << "Zadejte volbu: ";
		int choice;
		std::cin >> choice;
		std::cout << std::endl;
		std::cout << std::endl;

		switch (choice)
		{
		case 1:
			dbMenu->createTableDialog();
			break;
		case 2:
			dbMenu->openTableDialog();
			break;
		case 5:
			repeat = false;
			break;
		}
	}
}