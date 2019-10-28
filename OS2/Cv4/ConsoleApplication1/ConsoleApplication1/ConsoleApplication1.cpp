#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <assert.h>
#include <fstream>
#include <string>
using namespace std;

struct Params {
	const char *soubor, *filtr;
};



DWORD WINAPI hledat(CONST LPVOID lpParam) {
	int resultCount = 0;
	Params arg = *((Params*)lpParam);
	ifstream file(arg.soubor);
	string line;
	string filtr = arg.filtr;
	for (int i = 0; i < filtr.length(); i++) {
		filtr[i] = (tolower(filtr[i]));
	}
	while (getline(file, line)) {
		for (int i = 0; i < line.length(); i++) {
			line[i] = (tolower(line[i]));
		}
		if (line.find(filtr) == 0)
			resultCount++;
	}
	return resultCount;
}

int main()
{
	char Filtr[30];
	cout << "Zadej filtr: ";
	cin >> Filtr;
	Params arg1 = { "Jmena1.jpg", Filtr };
	Params arg2 = {"Jmena2.jpg", Filtr};
	HANDLE h[2];
	h[0] = CreateThread(NULL, 0, hledat, &arg1, 0, NULL);
	if (h[0] == NULL) {
		cout << "Thread creation failed," << endl;
		ExitProcess(3);
	}
	h[1] = CreateThread(NULL, 0, hledat, &arg2, 0, NULL);
	if (h[1] == NULL) {
		cout << "Thread creation failed," << endl;
		ExitProcess(3);
	}

	WaitForMultipleObjects(2, h, TRUE, INFINITE);

	assert(h[1] && h[0]);

	DWORD res1;
	GetExitCodeThread(h[0], &res1);
	DWORD res2;
	GetExitCodeThread(h[1], &res2);
	cout << "Names found by thread 1:" << res1 << endl;
	cout << "Names found by thread 2:" << res2 << endl;
	CloseHandle(h[0]);
	CloseHandle(h[1]);
}
