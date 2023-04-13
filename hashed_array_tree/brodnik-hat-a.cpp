#include <iostream>
#include <cmath>

#include "brodnik-hat-a.hpp"

using namespace std;

BrodnikHatA::BrodnikHatA(): dataBlockSize(1), pointerBlockSize(1), size(0), cap(1)
{
	name = "BrodnikHatA";
	pointerBlock = new int*[pointerBlockSize];
	pointerBlock[0] = new int[dataBlockSize];
}

BrodnikHatA::~BrodnikHatA()
{
	for (int i=0;i<pointerBlockSize;i++)
		delete[] pointerBlock[i];
	delete[] pointerBlock;
}

void BrodnikHatA::resize(int newPointerBlockSize)
{
	int newDataBlockSize = dataBlockSize + 1;
	int **newPointerBlock = new int*[newPointerBlockSize];
	int i;
	for (i=0;i<pointerBlockSize;i++)
		newPointerBlock[i] = pointerBlock[i];
	newPointerBlock[i] = new int[newDataBlockSize];
	delete[] pointerBlock;
	pointerBlock = newPointerBlock;
	dataBlockSize = newDataBlockSize;
	pointerBlockSize = newPointerBlockSize;
	cap += newDataBlockSize;
}

void BrodnikHatA::append(int n)
{
	if (size == cap)
		resize(pointerBlockSize + 1);
	pointerBlock[pointerBlockSize - 1][dataBlockSize - (cap - size)] = n;
	size++;
}

int BrodnikHatA::get(int pos)
{
	if (pos < 0 || pos >= size)
		return 0;
	int pointerBlockIndex = (int)((sqrt(8*pos + 1) - 1.0)/2.0);
	int dataBlockIndex = pos - (pointerBlockIndex*(pointerBlockIndex + 1))/2;
	return pointerBlock[pointerBlockIndex][dataBlockIndex];
}

void BrodnikHatA::print()
{
	for (int i=0;i<size;i++)
		cout << (*this).get(i) << " ";
	cout << endl;
}

void BrodnikHatA::printDes()
{
	cout << "pointerBlockSize: " << dataBlockSize << endl;
	cout << "dataBlockSize: " << dataBlockSize << endl;
	cout << "size: " << size << endl;
	cout << "cap: " << cap << endl;
}


const std::string &BrodnikHatA::getName()
{
	return name;
}

void BrodnikHatA::clear()
{
	// Free everything
	for (int i=0;i<pointerBlockSize;i++)
		delete[] pointerBlock[i];
	delete[] pointerBlock;
	// Reset fields
	dataBlockSize = 1;
	size = 0;
	cap = 1;
	pointerBlock = new int*[pointerBlockSize];
	pointerBlock[0] = new int[dataBlockSize];
}
