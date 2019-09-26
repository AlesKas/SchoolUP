#include "pch.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "Ovoce.cpp"
using namespace std;

struct hash_fun
{
	float operator () (const char *c) const
	{
		int len = strlen(c);
		return 31 * tolower(c[0]) + tolower(c[len - 1]) + len;
	}
};

struct equal_fun
{
	bool operator () (const char *c1, const char *c2) const
	{
		return(_stricmp(c1, c2) == 0);
	}
};

int main()
{
	unordered_map<const char *, float, hash_fun, equal_fun> m;

	for(OvoceCena ov : ovoceCena)
	{
		m.emplace(ov.ovoce, ov.cena);
	}

	for (const char* c : vypsatOvoce)
	{
		if (m.find(c) != m.end())
		{
			cout << c << " " << m[c] << endl;
		}
		else
			cout << c << " ???" << endl;
	}
}
