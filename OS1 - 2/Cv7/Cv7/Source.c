#include <stdio.h>
#include <stddef.h>

//_asm {
//	mov ebx, offset bar;
//	mov byte ptr[ebx], 'd';     // ulozi do bar.a = 'd'
//	mov cx, [ebx + 2];           // ulozi do cx hodnotu bar.b 
//	mov eax, [ebx + 4];          // ulozi do eax hodnotu bar.c
//	mov dword ptr[ebx + 3], eax // !!! provede nesmyslnou operaci
//}

struct foo {
	char a;
	short b;
	int c;
};

struct foo2 {
	short a;
	char b;
	int c;
};

struct foo3 {
	int a;
	char b;
	short c;
};

struct foo4 {
	char b;
	int a;
	short c;
};

struct foo bar;
struct foo2 baz;
struct foo3 quix;
struct foo4 aix;

struct osoba
{
	char* jmeno;			//0
	char* datum_narozeni;	//4
	unsigned char vyska;	//8
	unsigned short vaha;	//10
};

struct osoba db[30];
int index = 0;
int size = 12;

void db_add(char* jmeno, char* datum, unsigned char vyska, unsigned short vaha) {
	const char* error = "Error, databaze plna.";
	_asm {
		cmp index, 30
		jge wtf

		mov edx, 12
		mov eax, index
		imul edx
		
		mov ebx, jmeno
		mov [db + eax], ebx
		mov ebx, datum
		mov [db + eax + 4], ebx
		movzx ebx, vyska
		mov [db + eax + 8], ebx
		movzx ebx, vaha
		mov [db + eax + 10], ebx

		inc index
		jmp konec

	wtf:
		push error
		call printf
		add esp, 4
	konec:
	}
}

void db_print() {
	const char* formatStr = "%s, narozen: %s, vyska: %i, vaha: %i\n";
	char* format = "%s - %s - %i, %i\n";
	_asm {
		mov ebx, 0
	iter:
		cmp ebx, index
		jge end

		mov eax, 12
		mul ebx

		mov esi, [offset db]
		movzx edx, [esi + eax + 10]
		push edx
		movzx edx, [esi + eax + 8]
		push edx
		push [esi + eax + 4]
		push [esi + eax]

		push formatStr
		call printf
		add esp, 20

		inc ebx
		jmp iter

		end:
	}
}

int db_avg_height() {
	_asm {
		mov ebx, 0
		mov ecx, index
	for:
		mov eax, 12
		dec ecx
		mul ecx
		inc ecx

		mov esi, [offset db]
		movzx edx, [esi + eax + 8]
		add ebx, edx
		loop for

		mov eax, ebx
		cdq
		div index
	}
}

int db_avg_weight() {
	_asm {
		mov ebx, 0
		mov ecx, index
	for:
		mov eax, 12
		dec ecx
		mul ecx
		inc ecx

		mov esi, [offset db]
		movzx edx, [esi + eax + 10]
		add ebx, edx
		loop for

		mov eax, ebx
		cdq
		div index
	}
}

void struct_size() {
	bar.a = 0;
	bar.b = 100;
	bar.c = 200;
	printf("%i\n", sizeof(bar));
	baz.a = 100;
	baz.b = 0;
	baz.c = 200;
	printf("%i\n", sizeof(baz));
	quix.a = 200;
	quix.b = 0;
	quix.c = 100;
	printf("%i\n", sizeof(quix));
	aix.a = 0;
	aix.b = 200;
	aix.c = 100;
	printf("%i\n", sizeof(aix));
}

int main()
{
	struct_size();
	printf("-------------\n");
	db_add("Ales", "19.5.1998", 186, 65);
	db_add("Petr", "25.9.1988", 165, 95);
	db_add("Alena", "1.3.2000", 156, 55);
	db_add("Marek", "24.12.1", 190, 80);

	db_print();
	printf("Avg height: %d\n", db_avg_height());
	printf("Avg weight: %d\n", db_avg_weight());

	return 0;
}