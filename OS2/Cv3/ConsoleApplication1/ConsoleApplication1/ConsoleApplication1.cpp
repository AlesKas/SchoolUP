#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <chrono>
using namespace std;

int main()
{
	
	char cmdParams[5];
	cout << "Enter Time in ms:";
	cin >> cmdParams;

	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess("C:\\Users\\Aleš\\Documents\\GitHub\\SchoolUP\\OS2\\Cv3\\ConsoleApplication1\\Debug\\ConsoleApplication2.exe",
		cmdParams,
		NULL,
		NULL,
		FALSE,
		BELOW_NORMAL_PRIORITY_CLASS,
		NULL,
		NULL,
		&si,
		&pi)
		)
	{
		cout << "Unable to start process!" << endl;
		return -1;
	}
	WaitForSingleObject(pi.hProcess, INFINITE);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return 0;

}
