#include <iostream>

#include "list.hpp"
#include "sitarski-hat.hpp"
#include "brodnik-hat-a.hpp"

using namespace std;

int main(void)
{
	BrodnikHatA bha;
	SitarskiHat sh;
	for (int i=0;i<10;i++)
	{
		bha.append(i);
		sh.append(i);
	}
	bha.print();
	sh.print();
}
