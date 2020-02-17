#include <iostream>
#include <math.h>
using namespace std;

template <size_t n>
void int2bits(char (&arr)[n], int num) {
	int i;
	int size = n-1;
	for (i = 0; i < size; i++) {
		arr[i] = (num >> i) & 1;
	}
	arr[size] = '\0';
}

int bits2int(char* arr) {
	int number = 0;
	int i;
	for (i = 0; i < sizeof(arr); i++) {
		number <<= 1;
		number |= arr[i];
	}
	return number;
}

short encode_date(char day, char month, short year) {
	short code = 0;
	code = code | day;
	code = code | (month << 5);
	code = code | (year << 9);

	return code;
}

void decode_date(short date, int* day, int* month, int* year) {
	*day = date & 31;
	*month = (date >> 5) & 15;
	*year = (date >> 9) & 127;
}

void my_memcpy(void* dest, void* src, size_t size) {

}

template <size_t n>
void printDate(char(&arr)[n]) {
	int count = 0;
	for (int i = n-1; i >= 0; i--) {
		if (count != 4) {
			printf("%d", arr[i]);
			count++;
		}
		else {
			count = 1;
			printf("-%d", arr[i]);
		}
	}
	cout << endl;
}

int main()
{
	char array[33];
	int2bits(array, 101);
	for (int i = 32; i >= 0; i--) {
		printf("%d", array[i]);
	}
	std::cout << std::endl;
	char arr[] = { 1,1,1,1 };
	printf("%d\n", bits2int(arr));

	char arr2[16];
	char day = 3;
	char month = 4;
	short year = 97;
	int date = encode_date(day, month, year);

	int2bits(arr2, date);
	printDate(arr2);

	int dayOut;
	int monthOut;
	int yearOut;
	decode_date(date, &dayOut, &monthOut, &yearOut);
	printf("%i. %i. 19%i\n", day, month, year);
}