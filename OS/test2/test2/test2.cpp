#include "pch.h"
#include <iostream>
#include <stdio.h>

struct st {
	unsigned char a;
	short b;
	int c;
};

//void func(struct st a)
//{
//	_asm {
//		mov ebx, offset a
//		mov eax, [ebx]
//		mov ecx, [ebx + 2]
//		add eax, ecx
//		mov [ebx + 4], eax
//	}
//}

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
	std::cout << dist(5.3, 6.5) << std::endl;
	callFunc();
    std::cout << "Hello World!\n"; 
}