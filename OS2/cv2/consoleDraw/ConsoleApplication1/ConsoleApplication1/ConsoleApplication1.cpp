
#include "pch.h"
#include <iostream>

#define DLL extern __declspec(dllimport);
DLL void ctverec(int, char, char);
DLL void mriz(int, int, int, char);

int main()
{
	ctverec(7, '#', ':');
	std::cout << std::endl;
	mriz(5, 4, 3, '*');
	return 0;
}
