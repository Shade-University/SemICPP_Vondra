#include "MyIterator.h"

bool MyIterator::moveNext()
{
	return currentRow + 1 <= data.size();
}

Object** MyIterator::getRow() {
	Object** output = data.at(currentRow);
	currentRow++;

	return output;
}

int MyIterator::getRowId() {
	return currentRow++;
}

void MyIterator::close() {
	data.clear();
	data.shrink_to_fit(); //vector je p�ed�n jako hodnota (kopie), tud� sta�� smazat tento nov� vector.
}
