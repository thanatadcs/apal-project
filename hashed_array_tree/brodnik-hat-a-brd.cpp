#include <iostream>
#include <cmath>

#include "brodnik-hat-a-brd.hpp"

using namespace std;

BrodnikHatA::BrodnikHatA(): dataBlockCap(1), pointerBlockSize(1), pointerBlockCap(1), size(0), cap(1)
{
	name = "BrodnikHatABrd";
	pointerBlock = new int*[pointerBlockCap];
	pointerBlock[0] = new int[dataBlockCap];

	// For background-rebuilding
	pointerBlockRebuilding = new int*[2 * pointerBlockCap];
	pointerBlockRebuilding[0] = pointerBlock[0];
	pointerBlockRebuildingSize = 1;
}

BrodnikHatA::~BrodnikHatA()
{
	for (int i=0;i<pointerBlockCap;i++)
		delete[] pointerBlock[i];
	delete[] pointerBlock;

	// For background-rebuilding
	delete[] pointerBlockRebuilding;
}

void BrodnikHatA::resizePointerBlock(int newPointerBlockCap)
{
	delete[] pointerBlock;
	pointerBlock = pointerBlockRebuilding;
	pointerBlockCap = newPointerBlockCap;

	// For background-rebuilding
	int **newPointerBlockRebuilding = new int*[2 * newPointerBlockCap];
	pointerBlockRebuilding = newPointerBlockRebuilding;
	pointerBlockRebuildingSize = 0;
}

void BrodnikHatA::grow()
{
	if (pointerBlockSize == pointerBlockCap)
		resizePointerBlock(2 * pointerBlockCap);
	int newDataBlockCap = dataBlockCap + 1;
	pointerBlock[dataBlockCap] = new int[newDataBlockCap];
	pointerBlockSize += 1;
	cap += newDataBlockCap;
	dataBlockCap = newDataBlockCap;

	// For background-rebuilding
	pointerBlockRebuilding[pointerBlockRebuildingSize] = pointerBlock[pointerBlockRebuildingSize];
	pointerBlockRebuildingSize++;
	pointerBlockRebuilding[pointerBlockRebuildingSize] = pointerBlock[pointerBlockRebuildingSize];
	pointerBlockRebuildingSize++;
}

void BrodnikHatA::append(int n)
{
	if (size == cap)
		grow();
	pointerBlock[pointerBlockSize - 1][dataBlockCap - (cap - size)] = n;
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
	cout << "pointerBlockSize: " << pointerBlockSize << endl;
	cout << "pointerBlockCap: " << pointerBlockCap << endl;
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
	for (int i=0;i<pointerBlockSize;i++)
		delete[] pointerBlock[i];
	delete[] pointerBlock;
	// Reset fields
	dataBlockCap = 1;
	pointerBlockSize = 1;
	pointerBlockCap = 1;
	size = 0;
	cap = 1;
	pointerBlock = new int*[pointerBlockCap];
	pointerBlock[0] = new int[dataBlockCap];

	// For background-rebuilding
	delete[] pointerBlockRebuilding;
	pointerBlockRebuilding = new int*[2 * pointerBlockCap];
	pointerBlockRebuilding[0] = pointerBlock[0];
	pointerBlockRebuildingSize = 1;
}
