#include "pch.h"
#include <windows.h>
#include <iostream>
#include <assert.h>
#include <string>
#include <fstream>
#include <math.h>

using namespace std;

int main()
{
	char szBuffer[512];
	HANDLE hPipe;
	CHAR chBuf[512];
	BOOL fSuccess;
	DWORD cbRead, cbWritten, dwMode;
	LPCTSTR pipe = TEXT("\\\\.\\pipe\\Pipe1");


	hPipe = CreateFile(
		pipe,
		GENERIC_READ |
		GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);


	dwMode = PIPE_READMODE_MESSAGE;
	SetNamedPipeHandleState(
		hPipe,
		&dwMode,
		NULL,
		NULL);

	while (true)
	{

		printf("\n number: ");
		cin >> szBuffer;

		DWORD cbBytes;

		BOOL bResult = WriteFile(
			hPipe,
			szBuffer,
			strlen(szBuffer) + 1,
			&cbBytes,
			NULL);

		if (atoi(szBuffer) == 0)
		{
			break;
		}

		printf("\n base: ");
		cin >> szBuffer;

		cbBytes;

		bResult = WriteFile(
			hPipe,
			szBuffer,
			strlen(szBuffer) + 1,
			&cbBytes,
			NULL);


		bResult = ReadFile(
			hPipe,
			szBuffer,
			sizeof(szBuffer),
			&cbBytes,
			NULL);

		printf("\nServer sent the following message: %s", szBuffer);
	}

	CloseHandle(hPipe);

	getchar();
	return 0;
}