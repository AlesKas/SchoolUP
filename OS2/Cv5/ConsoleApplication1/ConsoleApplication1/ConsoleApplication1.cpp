#include "pch.h"
#include <windows.h>
#include <iostream>
#include <assert.h>
#include <string>
#include <fstream>
using namespace std;

CRITICAL_SECTION Cs1;
CRITICAL_SECTION Cs2;

struct Param {
	const char* filter;
	int* count;
	int* total;
	ifstream* file_in;
	ofstream* file_out;
};

DWORD WINAPI hledat(CONST LPVOID lpParam) {
	Param arg = *((Param*)lpParam);

	while (!arg.file_in->eof())
	{
		EnterCriticalSection(&Cs1);
		char size = arg.file_in->get();

		//char* name;
		//arg.file_in->read(&name, size);
		string s = "";
		for (int i = 0; i < size; i++)
		{
			char c;
			arg.file_in->get(c);
			s += c;
		}

		LeaveCriticalSection(&Cs1);

		EnterCriticalSection(&Cs2);
		if (s.find(arg.filter) == 0) {
			(*arg.count)++;
			(*arg.total)++;
			s += " ";
			char* c = new char[s.size() + 1];
			strcpy(c, s.c_str());
			arg.file_out->write(c, s.size());
			if ((*arg.total) % 10 == 0)
			{
				const char* newLine = "\n";
				arg.file_out->write(newLine, 1);
			}
		}
		LeaveCriticalSection(&Cs2);
	}

	ExitThread(0);
}

int main() {
	HANDLE hThreads[2];

	char Filtr[30];
	cout << "Zadej filtr: ";
	cin >> Filtr;

	ifstream file_in("Jmena.jpg");
	ofstream file_out("Jmena_out.txt");

	int count1 = 0;
	int count2 = 0;
	int total = 0;
	Param Param1 = { Filtr, &count1 ,&total,&file_in, &file_out };
	Param Param2 = { Filtr, &count2 ,&total,&file_in,&file_out };

	assert(hThreads[0] = CreateThread(NULL, 0, &hledat, &Param1, CREATE_SUSPENDED, NULL));

	assert(hThreads[1] = CreateThread(NULL, 0, &hledat, &Param2, CREATE_SUSPENDED, NULL));

	assert(hThreads[0] && hThreads[1]);
	InitializeCriticalSection(&Cs1);
	InitializeCriticalSection(&Cs2);


	ResumeThread(hThreads[0]);
	ResumeThread(hThreads[1]);

	WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);


	CloseHandle(hThreads[0]);
	CloseHandle(hThreads[1]);

	file_in.close();
	file_out.close();


	DeleteCriticalSection(&Cs1);
	DeleteCriticalSection(&Cs2);

	cout << "thread 1: " << count1 << endl;
	cout << "thread 2: " << count2 << endl;
}