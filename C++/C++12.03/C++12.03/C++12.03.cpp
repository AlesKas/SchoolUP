#include "pch.h"
#include <iostream>
#include <string>
#include <map>
#include "ABBA.cpp"
using namespace std;

typedef pair<int, char> klic;

bool automat(const char *vstup, map<klic, int> &mapa)
{
	int stav = 1;
	for (int i = 0; i < POCET; i++)
	{
		stav = mapa[klic(stav, vstup[i])];
	}
	return (stav < 0);
}

int main()
{
	map<klic, int> mapa;

	for (auto &i : ABBA)
	{
		mapa.emplace(klic(i.soucasnyStav, i.znak), i.nasledujiciStav);
	}

	cout << boolalpha << automat(vstup1, mapa) << endl;
	cout << boolalpha << automat(vstup2, mapa) << endl;

    cout << "Hello World!\n"; 
}

