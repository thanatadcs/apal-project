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
	unsigned int r = pos + 1;
	unsigned int k = bsr(r) - 1;
	unsigned int b = (r >> ((int)ceil(k/2.0))) & (1 << k/2) - 1;
	unsigned int e = r & ((1 << (int)ceil(k/2.0)) - 1);
	/*
	 * The code below is my own implementation to find the number of data block before k-th superblock.
	 * The reason for this is that the implementation of locate function in the paper Brodnik et al. 1999 did not work and 
	 * I suspected that it is wrong (maybe I have gone crazy after debugging for so long), 
	 * since p = 2^k - 1 is not the number of data block before k-th superblock, but it is the total number
	 * of elements before k-th superblock. So here is my (crying) attempt to do my own finding number of data block before k-th superblock.
	 */
	int preK = k - 1;
	int pow2 = 1 << preK/2; // 2^(preK/2)
	int numDataBlockBefore = preK % 2 == 0 ? pow2 * pow2 : pow2 * (pow2 + 1);
	if (preK < 0)
		numDataBlockBefore = 0;
	return pointerBlock[numDataBlockBefore + b][e];
}


void BrodnikHatB::print()
{
	for (int i=0;i<size;i++)
		cout << (*this).get(i) << " ";
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
	pointerBlockSize = 1;
	pointerBlockCap = 1;
	size = 0;
	cap = 1;
	superBlockIndex = 0;
	superBlockSize = 1;
	superBlockCap = 1;
	dataBlockIndex = 0;
	dataBlockSize = 0;
	dataBlockCap = 1;
	pointerBlock = new int*[pointerBlockCap];
	pointerBlock[0] = new int[dataBlockCap];
}
