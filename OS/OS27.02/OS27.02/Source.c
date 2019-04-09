#include <stdlib.h>
#include <stdio.h>

int avg_int(int a, int b, int c) {
	_asm {
		mov eax, a
		add eax, b
		add eax, c
		mov edx, 0
		cdq
		mov ebx, 3
		idiv ebx
	}
}
short avg_short(short a, short b, short c)
{
	_asm {
		mov ax, a
		add ax, b
		add ax, c
		cwd
		mov bx, 3
		idiv bx
	}
}

int sgn(int i)
{
	_asm {
		mov eax, i
		cmp eax, 0
		jg kladne
		jl zaporne
		jmp end
	kladne:
			mov eax, 1
			jmp end

	zaporne:
			mov eax, -1
	end:

	}


}

int min3(unsigned char a, short b, int c)
{
	int res;
	_asm {
		movsx eax, a
		movsx ebx, b
		cmp eax, ebx
		jg mensia
		cmp eax, c
		jg mensia
		mov res, eax
		jl end

	mensia: 
		cmp ebx, c
		jg mensib
		mov res, ebx
		jmp end

	mensib:
		mov ecx, c
		mov res, ecx
		jmp end

	end:
		
	}
	return res;
}

int kladne(int a, int b, int c)
{
	int res = 1;
	_asm {
		mov eax, a
		mov ebx, b
		mov ecx, c
		cmp eax,  0
		jl found
		cmp ebx, 0
		jl found
		cmp ecx, 0
		jl found
		jmp end
	found:
		mov res, 0
	end:
		
	}
	return res;
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

void main()
{
	printf("Hello world.\n");
	printf("%i\n", avg_int(-5,-4,-6));
	printf("%i\n", avg_short(30000,30,10));
	printf("%i\n", sgn(0));
	printf("%i\n", min3(4, 2, 10));
	printf("%i\n", kladne(-1, 2, 3));
	printf("%i\n", mocnina(3, 3));

	system("pause");
	return;
}