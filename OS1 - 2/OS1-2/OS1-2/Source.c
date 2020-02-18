#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int obvod_obdelnika(int a, int b) {
	_asm {
		mov eax, a
		add eax, b
		mov ebx, 2
		shl eax, 1
	}
}

int obsah_obdelnika(int a, int b) {
	_asm {
		mov eax, a
		mul b
	}
}

int obvod_ctverce(int a) {
	_asm {
		mov eax, a
		shl eax, 2
	}
}

int obsah_ctverce(int a) {
	_asm {
		mov eax, a
		mul a
	}
}

int obvod_trojuhelnika(int a, int b, int c) {
	_asm {
		mov eax, a
		add eax, b
		add eax, c
	}
}

int obvod_trojuhelnika2(int a) {
	_asm {
		mov eax, a
		mov ebx, 3
		mul ebx
	}
}

int obsah_trojuhelnika2(int a, int b) {
	_asm {
		mov eax, a
		mul b
		shr eax, 1
	}
}

int obsah_trojuhelnika3(int a, int va) {
	_asm {
		mov eax, a
		mul va
		shr eax, 1
	}
}

int objem_krychle(int a) {
	_asm {
		mov eax, a
		mul a
		mul a
	}
}

double heronuv_vzorec(int a, int b, int c) {
	int result;
	_asm {
		mov esi, a
		add esi, b
		add esi, c
		shr esi, 1

		mov eax, esi

		mov ebx, esi
		sub ebx, a
		mul ebx

		mov ebx, esi
		sub ebx, b
		mul ebx

		mov ebx, esi
		sub ebx, c
		mul ebx

		mov result, eax
	}
	return sqrt(result);
}

int main()
{
	printf("obvod_obdelnika %d\n", obvod_obdelnika(5, 6));
	printf("obsah_obdelnika %d\n", obsah_obdelnika(5, 6));
	printf("obvod_ctverce %d\n", obvod_ctverce(5));
	printf("obsah_ctverce %d\n", obsah_ctverce(5));
	printf("obvod_trojuhelnika %d\n", obvod_trojuhelnika(5, 6, 7));
	printf("obvod_trojuhelnika2 %d\n", obvod_trojuhelnika2(5));
	printf("obsah_trojuhelnika2 %d\n", obsah_trojuhelnika2(5, 6));
	printf("obsah_trojuhelnika3 %d\n", obsah_trojuhelnika3(5, 6));
	printf("objem_krychle %d\n", objem_krychle(5));
	printf("heronuv_vzorec %f\n", heronuv_vzorec(5, 6, 7));

	return 0;
}