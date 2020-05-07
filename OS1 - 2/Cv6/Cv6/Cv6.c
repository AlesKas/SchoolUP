#include <stdlib.h>
#include <stdio.h>
int arr[10];

unsigned long long measure_time_add()
{
	_asm {
		mov ecx, 50
		mov eax, 5

		rdtsc
		push edx
		push eax

		while:
			add eax, ecx
			add eax, ecx
			add eax, ecx
			add eax, ecx
		loop while

		mov esi, 4
		add esi, 5

		rdtsc
		sub eax, [esp]
		sbb edx, [esp + 4]
		add esp, 8
	}
}

unsigned long long measure_time_mov()
{
	_asm {
		mov ecx, 50

		rdtsc
		push edx
		push eax

		while:
			mov esi, 4
			mov esi, 5
			mov esi, 6
			mov esi, 7
		loop while

		rdtsc
		sub eax, [esp]
		sbb edx, [esp + 4]
		add esp, 8
	}
}

unsigned long long measure_time_mul ()
{
	_asm {
		mov ecx, 50
		mov eax, 5
		rdtsc
		push edx
		push eax

		while:
			mul ecx
			mul ecx
			mul ecx
			mul ecx
		loop while

		rdtsc
		sub eax, [esp]
		sbb edx, [esp + 4]
		add esp, 8
	}
}

unsigned long long measure_time_div()
{
	_asm {
		mov ecx, 50
		mov eax, 2
		rdtsc
		push edx
		push eax

		while:
			div eax
			cdq
			div eax
			cdq
			div eax
			cdq
			div eax
		loop while

		rdtsc
		sub eax, [esp]
		sbb edx, [esp + 4]
		add esp, 8
	}
}

unsigned long long measure_time_Shl()
{
	_asm {
		mov ecx, 50
		rdtsc
		push edx
		push eax
		mov eax, 2

		while:
			shl eax, 2
			shl eax, 2
			shl eax, 2
			shl eax, 2
		loop while

		rdtsc
		sub eax, [esp]
		sbb edx, [esp + 4]
		add esp, 8
	}
}

unsigned long long measure_time_lea()
{
	_asm {
		mov ecx, 50
		rdtsc
		push edx
		push eax

		while:
			lea eax, arr
			lea eax, arr
			lea eax, arr
			lea eax, arr
		loop while

		rdtsc
		sub eax, [esp]
		sbb edx, [esp + 4]
		add esp, 8
	}
}

unsigned long long constant_mul() {
	_asm {
		mov ecx, 50
		rdtsc
		push edx
		push eax

		mov eax, 5
		mov edx, 5

		while:
			mul edx
			mul edx
			mul edx
			mul edx
		loop while

		rdtsc
		sub eax, [esp]
		sub edx, [esp + 4]
		add esp, 8
	}
}

unsigned long long constant_shl() {
	_asm {
		mov ecx, 50
		rdtsc
		push edx
		push eax

		mov eax, 5

		while:
			shl eax, 2
			shl eax, 2
			shl eax, 2
			shl eax, 2
		loop while

		rdtsc
		sub eax, [esp]
		sub edx, [esp + 4]
		add esp, 8
	}
}

unsigned long long constant_lea() {
	_asm {
		mov ecx, 50
		rdtsc
		push edx
		push eax

		mov eax, 5
		mov edx, 5

		while:
			lea eax, [eax + 8 * edx]
			lea eax, [eax + 8 * edx]
			lea eax, [eax + 8 * edx]
			lea eax, [eax + 8 * edx]
		loop while

		rdtsc
		sub eax, [esp]
		sub edx, [esp + 4]
		add esp, 8
	}
}

unsigned long long constant_add() {
	_asm {
		mov ecx, 50
		rdtsc
		push edx
		push eax

		mov eax, 5
		mov edx, 5

		while:
			add eax, edx
			add eax, edx
			add eax, edx
			add eax, edx
		loop while

		rdtsc
		sub eax, [esp]
		sub edx, [esp + 4]
		add esp, 8
	}
}

int strtoint(char* str) {
	_asm {
		mov eax, 0
		mov ebx, str
		mov ecx, 0
		mov edi, 10

	iter:
		movzx esi, [ebx + ecx]
		cmp esi, '0'
		jl konec
		cmp esi, '9'
		jg konec

		sub esi, '0'
		mul edi
		add eax, esi
		inc ecx
		jmp iter

	konec:
	}
}

int main()
{
	unsigned long long timeMov = measure_time_mov();
	printf("Mov: %d\n", timeMov);
	unsigned long long timeAdd = measure_time_add();
	printf("Add: %d\n", timeAdd);
	unsigned long long timeMul = measure_time_mul();
	printf("Mul: %d\n", timeMul);
	unsigned long long timeDiv = measure_time_div();
	printf("Div: %d\n", timeDiv);
	unsigned long long timeShl = measure_time_Shl();
	printf("Shl: %d\n", timeShl);
	unsigned long long timeLea = measure_time_lea();
	printf("Lea: %d\n", timeLea);
	unsigned long long constMul = constant_mul();
	printf("Cons Mul: %d\n", constMul);
	unsigned long long constShl = constant_shl();
	printf("Const Shl: %d\n", constShl);
	unsigned long long constLea = constant_lea();
	printf("Const Lea: %d\n", constLea);
	unsigned long long constAdd = constant_add();
	printf("Const Add: %d\n", constAdd);
	printf("%d\n", strtoint("12345"));


	return 0;
}