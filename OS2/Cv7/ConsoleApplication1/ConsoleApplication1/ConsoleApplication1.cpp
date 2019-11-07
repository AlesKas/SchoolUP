#define _CRT_SECURE_NO_WARNINGS

#include "pch.h"
#include <iostream>		
#include <string>
#include <cmath>
#include <stdio.h>
#include <Windows.h>
#include <cassert>

using namespace std;

#define BUFFSIZE 512

string convert(int number, int base)
{
	string convertedNumber = "";

	while (number > 0)
	{
		char digit = number % base;
		if (digit < 10) {
			digit += '0';
		}
		else {
			digit = digit + 'A' - 10;
		}

		convertedNumber += digit;

		number /= base;
	}

	for (int i = 0; i < convertedNumber.length() / 2; i++) {
		swap(convertedNumber[i], convertedNumber[convertedNumber.length() - i - 1]);
	}

	return convertedNumber;
}

int main()
{
	BOOL fConnected;
	HANDLE hPipe;
	LPCTSTR pipeName = TEXT("\\\\.\\pipe\\Pipe1");

	hPipe = CreateNamedPipe(
		pipeName,
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE |
		PIPE_READMODE_MESSAGE |
		PIPE_WAIT,
		1,
		BUFFSIZE,
		BUFFSIZE,
		0,
		NULL);

	assert(hPipe != INVALID_HANDLE_VALUE);

	fConnected = ConnectNamedPipe(hPipe, NULL) ?
		TRUE :
		(GetLastError() == ERROR_PIPE_CONNECTED);

	cout << "Client connected" << endl;

	CHAR chRequest[BUFFSIZE];
	CHAR chReply[BUFFSIZE];
	DWORD cbBytesRead, cbWritten;
	BOOL fSuccess;

	while (1)
	{

		ReadFile(
			hPipe,
			chRequest,
			BUFFSIZE,
			&cbBytesRead,
			NULL);

		int number = stoi((char*)(LPSTR)chRequest);

		cout << "number: " << number << endl;

		if (number == 0)
		{
			break;
		}

		ReadFile(
			hPipe,
			chRequest,
			BUFFSIZE,
			&cbBytesRead,
			NULL);

		int base = stoi((char*)(LPSTR)chRequest);

		cout << "base: " << base << endl;

		string answer = convert(number, base);

		char* cstr = new char[answer.length() + 1];
		strcpy(cstr, answer.c_str());

		WriteFile(
			hPipe,
			cstr,
			strlen(cstr) + 1,
			&cbWritten,
			NULL);

	}

	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);

	return 0;
}