#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int nasobkyArr[10];
int countdownArr[10];
int mocninyArr[10];

void nasobky(short n) {
	_asm {
		mov ecx, 0
	foo:
		mov eax, ecx
		inc eax
		imul n
		mov[nasobkyArr + 4 * ecx], eax
		inc ecx
		cmp ecx, 10
		jl foo
	}

}

void finalCountdown()
{
	_asm
	{
		mov ecx, 10
		mov edx, 0
	foo:
		mov eax, ecx
		mov[countdownArr + 4 * edx], eax
		sub ecx, 1
		inc edx
		cmp edx, 10
		jl foo

	}
}

void mocniny()
{
	_asm {
		mov ecx, 1
		mov edx, 0
	foo:
		mov eax, ecx
		imul eax, ecx
		mov[mocninyArr + 4 * edx], eax
		inc ecx
		inc edx
		cmp edx, 10
		jl foo
	}
}

void mocniny2()
{
	int *arr = malloc(10 * sizeof(int));
	_asm {
		mov eax, arr
		mov ebx, 1
		mov ecx, 0
	iter:
		cmp ecx, 9
		jg end
		shl ebx, cl
		mov dword ptr[eax], ebx
		lea eax, [eax + 4]
		inc ecx
		mov ebx, 1
		jmp iter
	end:
	}
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int avg(unsigned int n)
{
	srand(time(NULL));
	short *arr2 = malloc(n * sizeof(short));
	for (int i = 0; i < n; i++)
	{
		arr2[i] = rand() % 20 - 10;
		printf("%d ", arr2[i]);
	}
	printf("\n");
	int res;

	_asm
	{
		mov ebx, [arr2]
		mov eax, 0
		mov edx, 0
	iter:
		movsx ecx, [ebx + 2 * edx]
		add eax, ecx
		inc edx
		cmp edx, n
		jl iter
		cdq
		idiv n
		mov res, eax
	}
	return res;
}

int minimum()
{
	srand(time(NULL));
	short *arr3 = malloc(10 * sizeof(short));
	for (int i = 0; i < 10; i++)
	{
		arr3[i] = rand() % 20 - 10;
		printf("%d ", arr3[i]);
	}
	printf("\n");
	int res;
	_asm {
		mov ebx, [arr3]
		mov ecx, 0
		movsx eax, [ebx + 2 * ecx]
		inc ecx
	iter:
		movsx edx, [ebx + 2 * ecx]
		cmp eax, edx
		jg mensiD
	incr:
		inc ecx
		cmp ecx, 10
		jl iter
		jge end

	mensiD:
		mov eax, edx
		jmp incr

	end:
		mov res, eax
	}
	return res;
}

int main()
{
	short n = 5;
	nasobky(n);
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", nasobkyArr[i]);
	}
	printf("\n");
	finalCountdown();
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", countdownArr[i]);
	}
	printf("\n");
	mocniny();
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", mocninyArr[i]);
	}
	printf("\n");
	mocniny2();
	printf("%d\n", avg(10));
	printf("-------------\n");
	printf("%d\n", minimum());

	//funguj
	system("pause");
}
