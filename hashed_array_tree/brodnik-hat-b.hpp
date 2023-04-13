#ifndef BRODNIK_HAT_B_H 
# define BRODNIK_HAT_B_H

#include "list.hpp"

class BrodnikHatB: public List
{
	private:
		int **pointerBlock;
		int superBlockIndex;
		int superBlockSize;
		int superBlockCap;
		int dataBlockIndex;
		int dataBlockSize;
		int dataBlockCap;
		int pointerBlockSize;
		int pointerBlockCap;
		int	size;
		int	cap;
		std::string name;

		void resizePointerBlock(int newPointerBlockCap);
		void grow();


	public:
		BrodnikHatB();
		~BrodnikHatB();

		void append(int n);
		int get(int pos);
		void print();
		void printDes();
		const std::string &getName();
		void clear();
};

#endif
