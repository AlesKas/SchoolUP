#include <stdlib.h>
#include <stdio.h>
int arr[10];

unsigned long long measure_time_add()
{
	_asm {
		rdtsc;
		push edx
		push eax;

		mov esi, 4
		add esi, 5

		rdtsc;
		sub eax, [esp];
		sbb edx, [esp + 4];
		add esp, 8;
	}
}

unsigned long long measure_time_mov()
{
	_asm {
		rdtsc;
		push edx
		push eax;

		mov esi, 4

		rdtsc;
		sub eax, [esp];
		sbb edx, [esp + 4];
		add esp, 8;
	}
}

unsigned long long measure_time_mul ()
{
	_asm {
		rdtsc;
		push edx
		push eax;

		mov eax, 4
		mov ebx, 3
		mul ebx

		rdtsc;
		sub eax, [esp];
		sbb edx, [esp + 4];
		add esp, 8;
	}
}

unsigned long long measure_time_div()
{
	_asm {
		rdtsc;
		push edx
		push eax;

		mov eax, 4
		mov ebx, 3
		cdq
		div ebx

		rdtsc;
		sub eax, [esp];
		sbb edx, [esp + 4];
		add esp, 8;
	}
}

unsigned long long measure_time_Shl()
{
	_asm {
		rdtsc;
		push edx
		push eax;

		mov eax, 4
		shl eax, 2

		rdtsc;
		sub eax, [esp];
		sbb edx, [esp + 4];
		add esp, 8;
	}
}

unsigned long long measure_time_lea()
{
	_asm {
		rdtsc;
		push edx
		push eax;

		lea eax, arr

		rdtsc;
		sub eax, [esp];
		sbb edx, [esp + 4];
		add esp, 8;
	}
}

unsigned long long measure_time_push()
{
	_asm {
		rdtsc;
		push edx
		push eax;

		mov eax, 5
		push eax
		add esp, 4

		rdtsc;
		sub eax, [esp];
		sbb edx, [esp + 4];
		add esp, 8;
	}
}

unsigned long long measure_time_pop()
{
	_asm {
		rdtsc;
		push edx
		push eax;

		mov eax, 5
		push eax
		pop eax

		rdtsc;
		sub eax, [esp];
		sbb edx, [esp + 4];
		add esp, 8;
	}
}

int strtoint(char* str) {

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
	unsigned long long timePush = measure_time_push();
	printf("Push: %d\n", timePush);
	unsigned long long timePop = measure_time_pop();
	printf("Pop: %d\n", timePop);



	return 0;
}