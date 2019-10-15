#include "stdafx.h"
#include <iostream>
using namespace std;

#define DLL __declspec(dllexport)

DLL void ctverec(int delka, char strana, char vnitr) {
	for (int i = 0; i < delka; i++)
	{
		for (int j = 0; j < delka; j++)
		{
			if (i == 0 || i == delka - 1 || j == 0 || j == delka - 1)
				cout << strana;
			else
				cout << vnitr;
		}
		cout << endl;
	}
}

DLL void mriz(int delka, int vodorovny, int svisly, char znak) {
	int row = delka * svisly;
	int col = delka * vodorovny;
	for (int i = 0; i <= row; i++) {
		for (int j = 0; j <= col; j++) {
			if (i == 0 || i % delka == 0 || j % delka == 0 || j == row || j == col) {
				cout << znak;
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
}