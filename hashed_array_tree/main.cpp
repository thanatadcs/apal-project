#include <iostream>

#include "list.hpp"
#include "sitarski-hat.hpp"
#include "brodnik-hat-a.hpp"
#include "brodnik-hat-b.hpp"

using namespace std;

int main(void)
{
	SitarskiHat sh;
	BrodnikHatA bha;
	BrodnikHatB bhb;
	for (int i=0;i<16;i++)
	{
		bhb.append(i);
	}
	//sh.print();
	//bha.print();
	bhb.print();
}
