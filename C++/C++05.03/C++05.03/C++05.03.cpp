#include "pch.h"
#include <iostream>
#include "Mince.jpg"
#include <set>
#include <string>
#include <iterator>
using namespace std;
int values[6] = { 1,2,5,10,20,50 };

void add(std::multiset<int> *m, int num)
{
	if (num > 0)
	{
		m->insert(num);
	}
	else
	{
		auto it = m->find(-num);
		if (it != m->end())
			m->erase(it);
	}
}
void writeValues(std::multiset<int> *m)
{
	for (int value : values)
	{
		auto element = m->equal_range(value);
		int count = distance(element.first, element.second);
		if (count)
		{
			cout << "M" << value << " " << count << "x" << endl;
		}
	}
}


int main()
{
	multiset<int> k;
	for (int i = 0; i < POCET; i++)
	{
		add(&k, pohyb[i]);
	}
	writeValues(&k);
}

