#include "pch.h"
#include <windows.h>
#include <iostream>
#include <assert.h>
#include <string>
#include <fstream>
#include <math.h>

using namespace std;

int prvocislo = 0;
bool endThis = false;

struct Params {
	int max;
	HANDLE generate;
	HANDLE write;
};

DWORD WINAPI hledejPrvocislo(CONST LPVOID lpParam) {
	Params arg = *((Params*)lpParam);
	int count = 0;
	
	for (int i = 2; i <= arg.max; i+=2) {
		bool isPrime = true;
		for (int j = 2; j < i; j++)
		{

			if ((i % j) == 0)
			{
				isPrime = false;
				break;
			}
		}			
		if (i == 2)
			{
				count++;
				WaitForSingleObject(arg.write, INFINITE);
				prvocislo = i;
				ReleaseSemaphore(arg.generate, 1, NULL);
				i = 3;
			}
		if (isPrime) {
			count++;
			WaitForSingleObject(arg.write, INFINITE);
			prvocislo = i;
			ReleaseSemaphore(arg.generate, 1, NULL);
		}

	}
	endThis = true;
	ReleaseSemaphore(arg.write, 1, NULL);
	ExitThread(count);
}

DWORD WINAPI tiskni(CONST LPVOID lpParam)
{
	int maxLine = 0;
	Params arg = *((Params*)lpParam);
	while (!endThis) {
		WaitForSingleObject(arg.generate, INFINITE);
		maxLine++;
		printf("%7d", prvocislo);
		if (maxLine == 10)
		{
			printf("\n");
			maxLine = 0;
		}
		ReleaseSemaphore(arg.write, 1, NULL);
	}
	ExitThread(0);
}


int main()
{
	string maxStr;
	cout << "Enter max: ";
	cin >> maxStr;
	int max = atoi(maxStr.c_str());
	if (max > 1){

		HANDLE generate = CreateSemaphore(NULL, 0, 1, NULL);
		HANDLE write = CreateSemaphore(NULL, 1, 1, NULL);

		Params params = { max, generate, write };

		HANDLE h[2];
		h[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)hledejPrvocislo, &params, CREATE_SUSPENDED, NULL);
		h[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)tiskni, &params, CREATE_SUSPENDED, NULL);
		ResumeThread(h[0]);
		ResumeThread(h[1]);

		WaitForSingleObject(h[0], INFINITE);
		WaitForSingleObject(write, INFINITE);

		assert(h[0] && h[1]);

		DWORD count;
		GetExitCodeThread(h[0], &count);
		cout << endl << "Count of prime numbers is " << count << endl;

		CloseHandle(h[0]);
		CloseHandle(h[1]);
		CloseHandle(generate);
		CloseHandle(write);
		
		return 0;
	}
}

