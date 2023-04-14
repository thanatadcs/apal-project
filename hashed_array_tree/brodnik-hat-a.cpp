#include <iostream>
#include <cmath>

#include "brodnik-hat-a.hpp"

using namespace std;

BrodnikHatA::BrodnikHatA(): dataBlockCap(1), pointerBlockSize(1), pointerBlockCap(1), size(0), cap(1)
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

void BrodnikHatA::resizePointerBlock(int newPointerBlockCap)
{
	int **newPointerBlock = new int*[newPointerBlockCap];
	for (int i=0;i<dataBlockCap;i++)
		newPointerBlock[i] = pointerBlock[i];
	delete[] pointerBlock;
	pointerBlock = newPointerBlock;
	pointerBlockCap = newPointerBlockCap;
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
	for (int i=0;i<pointerBlockCap;i++)
		delete[] pointerBlock[i];
	delete[] pointerBlock;
	// Reset fields
	dataBlockCap = 1;
	pointerBlockCap = 1;
	size = 0;
	cap = 1;
	pointerBlock = new int*[pointerBlockCap];
	pointerBlock[0] = new int[dataBlockCap];
}
