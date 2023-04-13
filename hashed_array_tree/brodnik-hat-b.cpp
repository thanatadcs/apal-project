#include <iostream>
#include <cmath>
#include <bitset>

#include "brodnik-hat-b.hpp"

using namespace std;

BrodnikHatB::BrodnikHatB(): pointerBlockSize(1), pointerBlockCap(1), size(0), cap(1), \
								superBlockIndex(0), superBlockSize(1), superBlockCap(1), \
									dataBlockIndex(0),  dataBlockSize(0), dataBlockCap(1)
{
	name = "BrodnikHatB";
	pointerBlock = new int*[pointerBlockCap];
	pointerBlock[0] = new int[dataBlockCap];
}

BrodnikHatB::~BrodnikHatB()
{
	for (int i=0;i<pointerBlockSize;i++)
		delete[] pointerBlock[i];
	delete[] pointerBlock;
}

void BrodnikHatB::resizePointerBlock(int newPointerBlockCap)
{
	int **newPointerBlock = new int*[newPointerBlockCap];
	for (int i=0;i<pointerBlockSize;i++)
		newPointerBlock[i] = pointerBlock[i];
	delete[] pointerBlock;
	pointerBlock = newPointerBlock;
	pointerBlockCap = newPointerBlockCap;
}

void BrodnikHatB::grow()
{
	if (superBlockSize == superBlockCap)
	{
		if (superBlockIndex % 2 != 0)
			superBlockCap *= 2;
		else
			dataBlockCap *= 2;
		superBlockSize = 0;
		superBlockIndex++;
	}
	if (pointerBlockSize == pointerBlockCap)
		resizePointerBlock(2 * pointerBlockCap);
	pointerBlock[dataBlockIndex + 1] = new int[dataBlockCap];
	pointerBlockSize++;
	dataBlockIndex++;
	superBlockSize++;
	dataBlockSize = 0;
	cap += dataBlockCap;
}


void BrodnikHatB::append(int n)
{
	if (size == cap)
		grow();
	pointerBlock[dataBlockIndex][dataBlockCap - (cap - size)] = n;
	dataBlockSize++;
	size++;
}

/*
 * Will be replace with BSR instruction in x86
 */
int bsr(unsigned int n)
{
  if (n == 0) {
        return 0;
    }
    int position = 0;
    while (n >>= 1) {
        ++position;
    }
    return position + 1; 
}


int BrodnikHatB::get(int pos)
{
	if (pos < 0 || pos >= size)
		return 0;
	unsigned int r = pos + 1;
	unsigned int k = bsr(r) - 1;
	unsigned int b = (r >> ((int)ceil(k/2.0))) & (1 << k/2) - 1;
	unsigned int e = r & ((1 << (int)ceil(k/2.0)) - 1);
	int preK = k - 1;
	int halfPreK = preK/2;
	int numBlockBefore = preK % 2 == 0 ? (1 << halfPreK) * (1 << halfPreK) : (1 << halfPreK) * ((1 << halfPreK) + 1);
	if (preK < 0)
		numBlockBefore = 0;
	return pointerBlock[numBlockBefore + b][e];
}


void BrodnikHatB::print()
{
	int dbs[] = {1, 2, 2, 2, 4, 4, 4, 4}; // Wiil fix this later
	int sbi = 0;
	int power = 0;
	for (int i=0;i<pointerBlockSize;i++)
	{
		for (int j=0;j<dbs[i];j++)
		{
			cout << pointerBlock[i][j] << " ";
		}
	}
	cout << endl;
}

void BrodnikHatB::printDes()
{
	cout << "pointerBlockSize: " << pointerBlockSize << endl;
	cout << "pointerBlockCap: " << pointerBlockCap << endl;
	cout << "superBlockIndex: " << superBlockIndex << endl;
	cout << "superBlockSize: " << superBlockSize << endl;
	cout << "superBlockCap: " << superBlockCap << endl;
	cout << "dataBlockIndex: " << dataBlockIndex << endl;
	cout << "dataBlockSize: " << dataBlockSize << endl;
	cout << "dataBlockCap: " << dataBlockCap << endl;
	cout << "size: " << size << endl;
	cout << "cap: " << cap << endl;
}


const std::string &BrodnikHatB::getName()
{
	return name;
}

void BrodnikHatB::clear()
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
