#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <iostream>

int avg_int(int a, int b, int c) {
	_asm {
		mov eax, a
		add eax, b
		add eax, c
		mov ebx, 3
		mov edx, 0
		cdq
		div ebx
	}
}

short avg_short(short a, short b, short c) {
	_asm {
		movsx eax, a
		movsx ebx, b
		movsx ecx, c
		add eax, ebx
		add eax, ecx
		cdq
		mov ebx, 3
		idiv ebx
	}
}

int sgn(int i) {
	_asm {
		cmp i, 0
		jl zaporne
		jg kladne
		mov eax, 0
		jmp konec
	kladne:
		mov eax, 1
		jmp konec
	zaporne:
		mov eax, -1
	konec:
	}
}

int min3(unsigned char a, short b, int c) {
	_asm {
		movzx ebx, a
		movsx ecx, b
		mov edx, c

		cmp ebx, ecx
		jg mensi1
		cmp ebx, edx
		jg mensi1
		//Checked all and A is smallest
		movsx eax, a
		jmp konec

	mensi1:
		//Checking B and C
		cmp ecx, edx
		jg mensi2
		movsx eax, b
		jmp konec

	mensi2:
		//C is smallest
		mov eax, c

	konec:
	}
}

int kladne(int a, int b, int c) {
	_asm {
		cmp a, 0
		jl found
		cmp b, 0
		jl found
		cmp c, 0
		jl found
		mov eax, 1
		jmp end
	found:
		mov eax, 0
	end:
	}
}

int mocnina(int n, unsigned int m) {
	_asm {
		mov eax, n
		mov ebx, 1
		
	iter:
		mul n
		inc ebx
		cmp ebx, m
		jl iter
	}
}

int main() {
	printf("%i\n", avg_int(10, 3, 4));
	printf("%i\n", avg_short(-20, 30, 10));
	printf("%i\n", sgn(-5));
	printf("%i\n", min3(4, 2, -10));
	printf("%i\n", kladne(1, 2, 3));
	printf("%i\n", mocnina(3, 3));
}