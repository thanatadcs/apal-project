#include <iostream>
#include <cmath>

#include "brodnik-hat-a.hpp"

using namespace std;

BrodnikHatA::BrodnikHatA(): dataBlockCap(1), pointerBlockCap(1), size(0), cap(1)
{
	name = "BrodnikHatA";
	pointerBlock = new int*[pointerBlockCap];
	pointerBlock[0] = new int[dataBlockCap];
}

BrodnikHatA::~BrodnikHatA()
{
	for (int i=0;i<pointerBlockCap;i++)
		delete[] pointerBlock[i];
	delete[] pointerBlock;
}

void BrodnikHatA::resize(int newPointerBlockSize)
{
	int newDataBlockSize = dataBlockCap + 1;
	int **newPointerBlock = new int*[newPointerBlockSize];
	int i;
	for (i=0;i<pointerBlockCap;i++)
		newPointerBlock[i] = pointerBlock[i];
	newPointerBlock[i] = new int[newDataBlockSize];
	delete[] pointerBlock;
	pointerBlock = newPointerBlock;
	dataBlockCap = newDataBlockSize;
	pointerBlockCap = newPointerBlockSize;
	cap += newDataBlockSize;
}

void BrodnikHatA::append(int n)
{
	if (size == cap)
		resize(pointerBlockCap + 1);
	pointerBlock[pointerBlockCap - 1][dataBlockCap - (cap - size)] = n;
	size++;
}

int BrodnikHatA::get(int pos)
{
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
	cout << "pointerBlockCap: " << dataBlockCap << endl;
	cout << "dataBlockCap: " << dataBlockCap << endl;
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
	for (int i=0;i<pointerBlockCap;i++)
		delete[] pointerBlock[i];
	delete[] pointerBlock;
	// Reset fields
	dataBlockCap = 1;
	size = 0;
	cap = 1;
	pointerBlock = new int*[pointerBlockCap];
	pointerBlock[0] = new int[dataBlockCap];
}
