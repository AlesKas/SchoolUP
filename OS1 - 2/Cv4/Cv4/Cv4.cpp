#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
int nasobkyArr[10];
int countdownArr[10];
short mocninyArr[10];

void nasobky(short n) {
    _asm {
		mov ax, n
		mov bx, n
        mov ecx, 0
	foo:
		mov word ptr [nasobkyArr + 4 * ecx], ax
		add ax, bx
		inc cx
		cmp ecx, 10
		jl foo
    }
}

void countdown() {
	_asm {
		mov al, 10
		mov cl, 0
	foo:
		mov byte ptr [countdownArr + 4 * ecx], al
		inc cl
		dec al
		cmp cl, 10
		jl foo
	}
}

void mocniny() {
	_asm {
		mov bx, 1
		mov ecx, 0
	foo:
		mov ax, bx
		imul ax, bx
		mov word ptr[mocninyArr +  2 * ecx], ax
		inc bx
		inc ecx
		cmp ecx, 10
		jl foo
	}
}

void mocniny2() {
	int *mocninyArr = (int*)malloc(10 * sizeof(int));
	_asm {
		mov eax, mocninyArr
		mov ebx, 1
		mov ecx, 0
	iter:
		cmp ecx, 9
		jg end
		shl ebx, cl
		mov [eax], ebx
		lea eax, [eax+4]
		inc ecx
		mov ebx, 1
		jmp iter
	end:
	}
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", mocninyArr[i]);
	}
	printf("\n\n");
}

int avg(unsigned int n) {
	short* arr2 = (short*)malloc(n * sizeof(short));
	srand((unsigned)time(0));
	for (int i = 0; i < n; i++) {
		arr2[i] = (rand() % 100) + 1;
		printf("%d ", arr2[i]);
	}
	printf("\n\n");
	_asm
	{
		mov ebx, arr2
		mov eax, 0
		mov ecx, 0
	iter:
		movsx edx, word ptr[ebx]
		add eax, edx
		lea ebx, [ebx + 2]
		inc ecx
		cmp ecx, n
		jl iter
		cdq
		idiv n
	}
}

int minimum() {
	int* arr3 = (int*)malloc(10 * sizeof(int));
	srand((unsigned)time(0));
	for (int i = 0; i < 10; i++) {
		arr3[i] = (rand() % 100) + 1;
		printf("%d ", arr3[i]);
	}
	printf("\n\n");
	_asm {
		mov ebx, [arr3]
		mov eax, [ebx]
		mov ecx, 0
	iter:
		inc ecx
		cmp ecx, 10
		je end
		mov edx, [ebx + 4 * ecx]
		cmp edx, eax
		jge iter
		mov eax, edx
		jmp iter
	end:
	}
}

int main()
{
	short n = 2;
	nasobky(n);
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", nasobkyArr[i]);
	}
	printf("\n\n");
	countdown();
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", countdownArr[i]);
	}
	printf("\n\n");
	mocniny();
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", mocninyArr[i]);
	}
	printf("\n\n");
	mocniny2();
	printf("avg: %d\n", avg(10));
	printf("-------------\n");
	printf("minimum: %d\n", minimum());
}
