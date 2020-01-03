#include "dbapi.h"
#include "helpful.h"
#include "DbMenu.h"

void showMainDialog(DbMenu dbMenu);
void showReadme();

int main() {
	Db* db = DbMenu::connectDbDialog();
	DbMenu dbMenu(db);
	showMainDialog(dbMenu);
	
	//end
	db->close();
	std::cout << "Dekuji za vyzkouseni aplikace. Doufam, ze vse fungovalo jak melo. :)" << std::endl;
	std::cin.get(); std::cin.get();
}
void showMainDialog(DbMenu dbMenu)
{
	bool repeat = true;

	while (repeat)
	{
		system("cls");
		std::cout << "Aplikace neni osetrena. Slouzi pouze k demonstraci a predpoklada se, ze uzivatel zadava validni a spravne data" << std::endl;
		std::cout << "Hlavni menu aplikace: " << std::endl;
		std::cout << "====================" << std::endl;
		std::cout << std::endl;

		std::cout << "1 - Vytvorit tabulku" << std::endl;
		std::cout << "2 - Otevrit tabulku" << std::endl;
		std::cout << "3 - Propojit tabulky" << std::endl;
		std::cout << "4 - Zobrazit propojene tabulky" << std::endl;
		std::cout << "5 - Ukoncit aplikaci" << std::endl;
		std::cout << "6 - Readme" << std::endl;


		std::cout << std::endl;
		std::cout << "Zadejte volbu: ";
		int choice;
		std::cin >> choice;
		std::cout << std::endl;
		std::cout << std::endl;

		switch (choice)
		{
		case 1:
			dbMenu.createTableDialog();
			break;
		case 2:
			dbMenu.openTableDialog();
			break;
		case 3:
			dbMenu.createMenuConnectTablesDialog();
			break;
		case 4:
			dbMenu.showConnectedTables();
			break;
		case 5:
			repeat = false;
			break;
		case 6:
			showReadme();
			break;
		}
	}
}

void showReadme()
{
	std::cout << "Aplikace slouzi pro otestovani a manipulaci nami vytvorenou db knihovnou." << std::endl;
	std::cout << "Aplikace neni osetrena, tudiz uzivatel musi zadavat spravna data, jinak hrozi pad programu." << std::endl;
	std::cout << "Po pripojeni (nebo vytvoreni) Db uzivatel muze vytvaret tabulky. Zmeny se ukladaji." << std::endl;
	std::cout << "Dale muze projit do modu manipulace s tabulkou, kde muze pridavat, mazat a zobrazit zaznamy. Zmeny se projevi pri commitu." << std::endl;
	std::cout << "Propojovani tabulek nam umozni propojit dve relacni tabulky podle vybranych sloupcu" << std::endl;
	std::cout << "Vybrane sloupce musi byt datoveho typu integer (do budoucna by se dalo rozsirit na vse)" << std::endl;
	std::cout << "Po propojeni si je muzeme zobrazit. Zmeny se neuchovavaji. Po ukonceni aplikace relace zmizi (do budoucna by se dalo uchovat v souborech)" << std::endl;
	std::cout << std::endl;
	system("pause");
}
