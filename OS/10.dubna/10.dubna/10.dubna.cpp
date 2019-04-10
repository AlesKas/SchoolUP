#include <stdio.h>
#include <stdlib.h>
#include "pch.h"
#include <iostream>

_declspec(naked) int min1(int a, int b)
{
	_asm {
		push ebp
		mov ebp, esp

		mov eax, [ebp + 8]
		mov ebx, [ebp + 12]
		cmp eax, ebx
		jl mensi
		mov eax, ebx
	mensi:
		mov esp, ebp
		pop ebp
		ret
	}

}

_declspec(naked) int min2(int a, int b)
{
	_asm
	{
		push ebp
		mov ebp, esp

		mov eax, ecx
		mov ebx, [ebp + 12]
		cmp eax, ebx
		jl mensi
		mov eax, ebx
	mensi:
		mov esp, ebp
		pop ebp
		ret
	}
}

_declspec(naked) int min3(int a, int b)
{
	_asm {
		mov eax, ecx
		mov ebx, edx
		cmp eax, ebx
		jl mensi
		mov eax, ebx
	mensi:
		ret
	}
}

_declspec(naked) int facCDECL(int num)
{
	_asm {
		push ebp
		mov ebp, esp

		mov eax, [ebp + 8]
		mov ecx, eax
	iter:
		cmp ecx, 1
		jle end
		dec ecx
		imul eax, ecx
		jmp iter
	end:
		mov esp, ebp
		pop ebp
		ret
	}
}

_declspec(naked) int facFAST(int num)
{
	_asm {
		mov eax, edx
		mov ecx, eax
	iter:
		cmp ecx, 1
		jle end
		dec ecx
		imul eax, ecx
		jmp iter
	end:
		ret
	}
}

_declspec(naked) unsigned int fibC(int n)
{
	_asm {
		cmp n, 1
		jle mensi

		mov ecx, n
		sub ecx, 1
		push ecx
		call fibC
		mov ebx, eax
		add esp, 4

		mov ecx, n
		sub ecx, 2
		push ecx
		call fibC
		add esp, 4

		add eax, ebx

		jmp end

	mensi :
		mov eax, n

	end :

	}
}

_declspec(naked) int fibCDECL(int num)
{
	_asm {
		push ebp
		mov ebp, esp
		push ebx

		mov eax, [ebp + 8]
		cmp eax, 1
		jle mensi
		mov ecx, eax
		dec ecx
		push ecx
		call fibCDECL
		mov esi, eax
		add esp, 4

		mov ecx, eax
		sub ecx, 2
		push ecx
		call fibCDECL
		add esp, 4

		add eax, esi
		mov ebx, eax
		jmp end

	mensi:
		mov eax, num
	end:

		pop ebx
		mov esp, ebp
		pop ebp
		ret

	}
}

void doFunc()
{
	const char *min = "Minimum je %d\n";
	const char *fact = "%d! = %d\n";
	const char *fib = "%d. fib cislo = %d\n";
	int num = 5;
	_asm
	{
		push dword ptr -10
		push dword ptr 5
		call min1
		add esp, 8

		push eax
		push min
		call printf
		add esp, 8

		push dword ptr 5
		mov ecx, -5
		call min2
		add esp, 4

		push eax
		push min
		call printf
		add esp, 8

		mov edx, 5
		mov ecx, -10
		call min3

		push eax
		push min
		call printf
		add esp, 8

		push num
		call facCDECL
		add esp, 4

		push eax
		push num
		push fact
		call printf
		add esp, 12
 
		mov edx, num
		call facFAST

		push eax
		push num
		push fact
		call printf
		add esp, 12

		push 6
		call fibCDECL
		add esp, 4

		push eax
		push 6
		push fib
		call printf
		add esp, 12
	}
}

int main()
{
	doFunc();
}
