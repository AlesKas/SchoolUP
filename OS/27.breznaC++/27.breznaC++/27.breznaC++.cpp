#include "pch.h"
#include <iostream>
using namespace std;

typedef struct datumNarozeni
{
	unsigned char den;
	unsigned char mesic;
	unsigned short rok;
}datumNarozeni; //4

typedef struct person {
	const char* jmeno;
	unsigned char vyska;
	unsigned short vaha;
	datumNarozeni narozeni;
}Person; //12

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

	_asm
	{
	movsx eax, index
	mov edx, 12
	imul edx
	mov ecx, eax

	mov eax, name
	mov[dat + ecx], eax
	movsx eax, height
	mov[dat + 2 + ecx], eax
	movsx eax, weight
	mov[dat + 4 + ecx], eax
	mov eax, dN
	mov[dat + 6 + ecx], eax

	inc index
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
	asm_add("Jakub Katzer", jk, 182, 87);
	datumNarozeni jb = { 18, 6, 1968 };
	asm_add("James Bond", jb, 179, 70);
	db_print();

	printf("Prumerna vyska: %f\n", db_avg_height());
	printf("Prumerna vaha: %f\n", db_avg_weight());

	

}

