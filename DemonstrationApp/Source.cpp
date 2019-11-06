#include "dbapi.h"
#include <iostream>
#include <string>

int main() {
	// Vytvoøení db
	Db* db = Db::open("testdb");

	std::cin.get();
	return 0;
}
