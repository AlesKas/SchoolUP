#include <stdio.h>
#include "pch.h"
#include <iostream>
using namespace std;
char arr2[] = { 1,2,3,4,5,6,7,8,9,0 };
extern "C" int ReturnOne();
extern "C" void testuj();
struct T{
char a, b, c, d, e, f, g;
};

int ObsahObdelnika(int a, int b) {
	_asm {
		mov eax, a
		imul eax, b
	}
}
int ObvodObdelnika(int a, int b) {
	_asm {
		mov eax, a
		add eax, b
		shl eax, 1
	}
}
int obsahTrojuhelnika(int a, int va)
{
	_asm {
		mov eax, a
		mul va
		sar eax, 1
	}
}
void xchng(int a, int b)
{
	printf("%d %d\n", a, b);
	_asm {
		mov eax, a
		mov ebx, b
		add eax, ebx
		sub ebx, eax
		add eax, ebx
		mov a, eax
		mov eax, 0
		sub eax, ebx	
		mov b, eax
	}
	printf("%d %d\n", a, b);
}

//T CtiPrvekPole(T *pole, int index) {
//	_asm {
//		mov eax, pole
//		mov ebx, index
//		cdq
//		mov eax, [eax + ebx * 7]
//	}
//}

void _7th8th(char *pole) {
	_asm {
		mov eax, pole
		mov bl, [eax + 2]
		mov[eax + 7], bl
		mov bl, [eax + 3]
		mov[eax + 9], bl
	}
}
void _7th8th2() {
	const char * form = "%d";
	_asm {
		mov bx, word ptr [offset arr2 + 2]
		mov byte ptr[offset arr2 + 7], bl
		mov byte ptr[offset arr2 + 9], bh
	}
}

void memcpz(char *source, char *dest, int len) {
	_asm {
		mov esi, source
		mov edi, dest
		mov ecx, len
		mov ebx, 0
	opakuj:
		mov al,	[esi + ebx]
		mov [edi + ebx], al
		inc ebx
		loop opakuj
	}
}

void memcpz2(char *source, char *dest, int len) {
	_asm {
		mov esi, source
		mov edi, dest
		mov ecx, len
	opakuj:
		mov al, [esi]
		inc esi
		mov [edi], al
		inc edi
		loop opakuj
	}
}

int sum(int *pole, int len) {
	_asm {
		mov esi, pole
		mov ecx, len
		mov eax, 0
	opakuj:
		add eax, [esi]
		add esi, 4
		loop opakuj
	}
}

void clearmem(int *p, int len) {
	_asm {
		mov esi, p
		mov ecx, len
	opakuj:
		mov [esi], 0
		add esi, 4
		loop opakuj
	}
}

void indexarr(int *p, int len) {
	_asm {
		mov esi, p
		mov ecx, len
		mov eax, 0
	opakuj :
		mov[esi], eax
		inc eax
		add esi, 4
		loop opakuj
	}
}

void testab(int a, int b, const char *pozdrav) {
	_asm {
		cmp a, 0
		jng konec
		test b, 1
		jnz konec
		push pozdrav
		call dword ptr printf
		add esp, 4
	konec:
	}
}

int asm_strlen(const char *text) {
	_asm {
		mov eax, text
		mov ecx, 0
	zacatek:
		cmp byte ptr[eax + ecx], 0
		jz konec
		inc ecx
		jmp zacatek
	konec:
		mov eax, ecx
	}
}

int asm_strlen2(const char *text) {
	_asm {
		mov eax, text
		dec eax
	cycle:
		inc eax
		cmp byte ptr[eax], 0
		jnz cycle
		sub eax, text
	}
}

int kladna_zaporna(int *pole, int delka) {
	_asm {
		mov esi, pole
		mov ecx, delka
		mov eax, 0
	opakuj:
		cmp dword ptr[esi], 0
		je dalsi
		jg kladne
		dec eax
		jmp dalsi
	kladne:
		inc eax
	dalsi:
		add esi, 4
		loop opakuj

		cmp eax, 0
		je konec
		mov eax, 1
		jg konec
		mov eax, -1
	konec:
	}
}
void indexarrSL(int *p, int len)
{
	_asm {
		mov esi, p
		mov ecx, len
		mov eax, 0
	opakuj:
		test eax, 1
		jz jump1
		neg eax
	jump1:
		mov[esi], eax
		inc eax
		add esi, 4
		loop opakuj
	}
}

int main()
{
    cout << "Hello World!\n"; 
	cout << ObsahObdelnika(4, 5) << endl;
	char b, c;
	_asm {
		mov word ptr b, 512
	}
	printf("b = %i c = %i \n", b, c);
	cout << ObvodObdelnika(4, 5) << endl;
	cout << obsahTrojuhelnika(5, 6) << endl;
	xchng(5, 10);
	char arr[] = { 1,2,3,4,5,6,7,8,9,0 };
	_7th8th(arr);
	for (int i = 0; i < 10; i++) {
		printf("%d", arr[i]);
	}
	cout << endl;
	_7th8th2();
	for (int i = 0; i < 10; i++) {
		printf("%d", arr2[i]);
	}
	cout << endl;
	char sou[] = { 1,2,3,4,5,6,7,8,9,0 };
	char dest[10];
	memcpz(sou, dest, 10);
	for (int i = 0; i < 10; i++) {
		printf("%d", dest[i]);
	}
	cout << endl;
	char sou2[] = { 1,2,3,4,5,6,7,8,9,0 };
	char dest2[10];
	memcpz(sou2, dest2, 10);
	for (int i = 0; i < 10; i++) {
		printf("%d", dest2[i]);
	}
	cout << endl;
	int soui[] = { 1,2,3,4,5,6,7,8,9,0 };
	cout << sum(soui, 10) << endl;
	clearmem(soui, 10);
	for (int i = 0; i < 10; i++) {
		printf("%d", soui[i]);
	}
	cout << endl;
	indexarr(soui, 10);
	for (int i = 0; i < 10; i++) {
		printf("%d", soui[i]);
	}
	cout << endl;
	testab(0, 3, "nazdar\n");
	cout << asm_strlen("Hello World!") << endl;
	cout << asm_strlen2("Hello World!") << endl;
	cout <<ReturnOne() << endl;
	testuj();
	indexarrSL(soui, 10);
	for (int i = 0; i < 10; i++) {
		printf("%d", soui[i]);
	}
	cout << endl;
}
