#include "pch.h"
#include <iostream>
using namespace std;

typedef struct datumNarozeni
{
	unsigned char den;
	unsigned char mesic;
	unsigned short rok;
}datumNarozeni;

typedef struct person {
	const char* jmeno;
	unsigned char vyska;
	unsigned short vaha;
	datumNarozeni narozeni;
}Person;

Person dat[30];
short index = 0;

int db_add(const char* name, datumNarozeni dN, unsigned char height, unsigned short weight)
{
	if (index == 29)
		return -1;

	Person newP;
	newP.jmeno = name;
	newP.narozeni = dN;
	newP.vyska = height;
	newP.vaha = weight;

	dat[index] = newP;
	index++;
	return 1;
}

int asm_add(const char* name, datumNarozeni dN, unsigned char height, unsigned short weight)
{
	Person newP;
	_asm
	{
		movzx eax, index
		cmp eax, 29
		je error

		mov eax, dat

		mov ebx, offset newP
		mov [ebx], name
		mov [ebx + 2], dN
		mov [ebx + 4], height
		mov [ebx + 6], weight

		mov [eax + index], ebx
		mov eax, 1
		jmp end

	error:
		mov al, 0
	end:
	}
}

void db_print()
{
	for (int i = 0; i < index; i++)
	{
		Person o = dat[i];
		printf("%s narozen %i.%i.%i vaha: %d, vyska: %d\n", o.jmeno, o.narozeni.den, o.narozeni.mesic, o.narozeni.rok, o.vaha, o.vyska);
	}
}

float db_avg_height()
{
	if (index == 0)
		return 0;

	float avg = 0;
	for (int i = 0; i < index; i++)
	{
		Person o = dat[i];
		avg += o.vyska;
	}
	return avg / index;
}

float db_avg_weight()
{
	if (index == 0)
		return 0;

	float avg = 0;
	for (int i = 0; i < index; i++)
	{
		Person o = dat[i];
		avg += o.vaha;
	}
	return avg / index;
}

int main()
{
	datumNarozeni jk = {13, 2, 1996};
	db_add("Jakub Katzer", jk, 182, 87);
	datumNarozeni jb = { 18, 6, 1968 };
	db_add("James Bond", jb, 179, 70);

	db_print();

	printf("Prumerna vyska: %f\n", db_avg_height());
	printf("Prumerna vaha: %f\n", db_avg_weight());

	

}

