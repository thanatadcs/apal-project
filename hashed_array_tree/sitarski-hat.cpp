#include <iostream>

#include "sitarski-hat.hpp"

using namespace std;

SitarskiHat::SitarskiHat(): dataBlockCap(2), logDbs(1), size(0)
{
	name = "hat";
	cap = dataBlockCap << logDbs;
	indexBlocks = new int*[dataBlockCap];
	for (int i=0;i<dataBlockCap;i++)
		indexBlocks[i] = new int[dataBlockCap];
}

SitarskiHat::~SitarskiHat()
{
	for (int i=0;i<dataBlockCap;i++)
		delete[] indexBlocks[i];
	delete[] indexBlocks;
}

void SitarskiHat::resize(int newDataBlockSize)
{
	int **newDataBlocks = new int*[newDataBlockSize];
	for (int i=0;i<newDataBlockSize;i++)
		newDataBlocks[i] = new int[newDataBlockSize];
	int ni = 0, nj = 0;
	for (int i=0;i<dataBlockCap;i++)
	{
		for (int j=0;j<dataBlockCap;j++)
		{
			newDataBlocks[ni][nj++] = indexBlocks[i][j];
			if (nj == newDataBlockSize) 
			{
				nj = 0;
				ni++;
			}
		}
		delete[] indexBlocks[i];
	}
	delete[] indexBlocks;
	indexBlocks = newDataBlocks;
	dataBlockCap = newDataBlockSize;
	logDbs++;
	cap = dataBlockCap << logDbs;
}

void SitarskiHat::append(int n)
{
	if (size == cap)
		resize(dataBlockCap << 1);
	indexBlocks[size >> logDbs][size & ((1 << logDbs) - 1)] = n;
	size++;
}

int SitarskiHat::get(int pos)
{
	if (pos < 0 || pos >= size)
		return 0;
	return indexBlocks[pos >> logDbs][pos & ((1 << logDbs) - 1)];
}

void SitarskiHat::print()
{
	for (int i=0;i<size;i++)
		cout << (*this).get(i) << " ";
	cout << endl;
}

void SitarskiHat::printDes()
{
	cout << "DBS: " << dataBlockCap << endl;
	cout << "logDBS: " << logDbs << endl;
	cout << "size: " << size << endl;
	cout << "cap: " << cap << endl;
}


const std::string &SitarskiHat::getName()
{
	return name;
}

void SitarskiHat::clear()
{
	// Free everything
	for (int i=0;i<dataBlockCap;i++)
		delete[] indexBlocks[i];
	delete[] indexBlocks;
	// Reset fields
	dataBlockCap = 2;
	logDbs = 1;
	size = 0;
	cap = dataBlockCap << logDbs;
	indexBlocks = new int*[dataBlockCap];
	for (int i=0;i<dataBlockCap;i++)
		indexBlocks[i] = new int[dataBlockCap];
}