#include <stdio.h>
#include <stdlib.h>
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
	mensi :
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
		mensi :
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
	mensi :
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
		iter :
		cmp ecx, 1
		jle end
		dec ecx
		imul eax, ecx
		jmp iter
	end :
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
	iter :
		cmp ecx, 1
		jle end
		dec ecx
		imul eax, ecx
		jmp iter
	end :
		ret
	}
}


_declspec(naked) int fibCDECL(int num)
{
	_asm {
		push ebp
		mov ebp, esp
		push ebx

		movsx ecx, [ebp + 8]
		cmp ecx, 1
		jle mensi

		sub ecx, 1
		push ecx
		call fibCDECL
		mov ebx, eax
		add esp, 4

		movsx ecx, [ebp + 8]
		sub ecx, 2
		push ecx
		call fibCDECL
		add esp, 4

		add eax, ebx

		jmp end

	mensi :
		movsx eax, [ebp + 8]
	end :

		pop ebx
		mov esp, ebp
		pop ebp
		ret

	}
}

__declspec(naked) int fibFastcall(int num) {
	_asm {
		push esi
		push edi

		cmp ecx, 1
		jle one

		dec ecx
		mov esi, ecx
		call fibFastcall
		mov edi, eax

		dec esi
		mov ecx, esi
		call fibFastcall
		add eax, edi


		jmp end
	one :
		cmp ecx, 0
		je zero
		mov eax, 1
		jmp end
	zero :
		mov eax, 0
	end :
		pop edi
		pop esi
		ret
	}
}

void doFunc()
{
	const char* min = "Minimum je %d\n";
	const char* fact = "%d! = %d\n";
	const char* fib = "%d. fib cislo = %d\n";
	int num = 5;
	_asm
	{
		push dword ptr - 10
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

		mov ecx, 6
		call fibFastcall

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