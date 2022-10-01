#include <iostream>
#include <cmath>
#include "FileWAV.h"

int main()
{
	std::cout<<"I use GCC\n";
	FileWAV w;
	w.create(2,500,1);
	w.setsamplerate(8000);
	for(int i = 0; i< 500;i++)
	{
		w.sample16(i) = (i%2 == 0) ? 0x7fff : 0x8000;
	}
	std::cout<<w.size();
	w.save("Sound.wav");
	return 0;
}
