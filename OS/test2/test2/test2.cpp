#include "pch.h"
#include <iostream>
#include <stdio.h>

struct st {
	unsigned char a;
	short b;
	int c;
};

void func()
{
	struct st a;
	a.a = 3;
	a.b = 4;
	_asm {
		lea ebx, a
		movsx eax, byte ptr[ebx]
		movsx ecx, word ptr[ebx + 2]
		cdq
		imul ecx
		mov dword ptr [ebx + 4], eax
	}
	std::cout << a.c << std::endl;
}

double dist(double a, double t)
{
	double s;
	_asm {
		push 2
		fld a
		fidiv dword ptr[esp]
		add esp, 4 

		fld t
		fmul st, st
		
		fmul
		fst s
	}
	return s;
}

_declspec(naked) int avg(int a, int b, int c)
{
	_asm { 
		push ebp
		mov ebp, esp

		mov eax, [ebp + 8]
		add eax, ecx
		add eax, edx
		cdq
		mov ebx, 3
		idiv ebx


		mov esp, ebp
		pop ebp
		ret
		
	}
}

void callFunc()
{
	const char* format = "avg  = %d\n";
	_asm {
		mov ecx, 10
		mov edx, -20
		push 42
		call avg
		add esp, 4

		push eax
		push format
		call printf
		add esp, 8
	}
}

int main()
{
	func();
	std::cout << dist(5.3, 6.5) << std::endl;
	callFunc();
    std::cout << "Hello World!\n"; 
}