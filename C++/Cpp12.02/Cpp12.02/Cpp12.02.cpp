#include "pch.h"
#include <iostream>
#include <string>
using namespace std;
int main()
{
	string v("In the C++ programming language, the retez trida is a standard representation for a retez of a text.\n"
		"The trida provides some typical retez operations like comparison, conscentration, find and replace.\n");
	string s[]{ string("retez"), string("string"), string("trida"), string("class") };
	cout << v << endl;
	for (int i = 0; i <= 2; i = i + 2)
	{
		int start = v.rfind(s[i]);
		while (start != -1)
		{
			v.replace(start, s[i].size(), s[i + 1]);
			start = v.rfind(s[i]);
		}
	}
	cout << v;
}
