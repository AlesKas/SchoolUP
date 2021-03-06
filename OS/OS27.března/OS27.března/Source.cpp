#include <stdio.h>
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

void db_print()
{
	for (int i = 0; i < index; i++)
	{
		Person o = dat[i];
		printf("%s narozen %i.%i.%i vaha: %d, vyska: %d\n", o.jmeno, o.narozeni.den, o.narozeni.mesic, o.narozeni.rok, o.vaha, o.vyska);
	}
}

int maint()
{
	datumNarozeni dt;
	dt.den = 13;
	dt.mesic = 2;
	dt.rok = 1998;
	db_add("Jakub Katzer", dt, 180, 88);
	db_print();

	return 0;
}