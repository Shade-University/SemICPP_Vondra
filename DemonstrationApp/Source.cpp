#include "dbapi.h"
#include <iostream>
#include <string>

int main() {
	// Vytvo�en� db
	Db* db = Db::open("testdb");

	std::cin.get();
	return 0;
}
