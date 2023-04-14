#ifndef BRODNIK_HAT_A_H 
# define BRODNIK_HAT_A_H

#include "list.hpp"

class BrodnikHatA: public List
{
	private:
		int **pointerBlock;
		int **pointerBlockRebuilding; // For background-rebuilding (Brd)
		int pointerBlockRebuildingSize; // For background-rebuilding (Brd)
		int dataBlockCap;
		int pointerBlockSize;
		int pointerBlockCap;
		int	size;
		int	cap;
		std::string name;

		void grow();
		void resizePointerBlock(int newPointerBlockCap);


	public:
		BrodnikHatA();
		~BrodnikHatA();

		void append(int n);
		int get(int pos);
		void print();
		void printDes();
		const std::string &getName();
		void clear();
};

#endif
