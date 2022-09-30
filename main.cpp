#include <iostream>
#include "FileWAV.h"

int main()
{
	int i = 12;
	std::cout<<"I use GCC\n";
	std::cout<<reinterpret_cast<char *>(&i)<<'\n';
	return 0;
}
