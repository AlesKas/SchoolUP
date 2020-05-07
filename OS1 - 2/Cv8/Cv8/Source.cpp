#include <iostream>
#include <stdio.h> 
#include <bitset>

using namespace std;

int mask(int p, int n) {
	_asm {
		mov eax, 0
		mov ebx, p
		mov edx, n
		dec edx

	rec1:
		add eax, 1
		shl eax, 1
		dec edx

		cmp edx, 0
		jg rec1

		add eax, 1

		cmp ebx, 0
		je konec

	rec2:

		shl eax, 1
		dec ebx

		cmp ebx, 0
		jg rec2
	konec:
	}
}

int divide2(int a, int n, int* res, int* rest) {
	_asm {
		mov eax, a
		mov edx, n
		mov esi, res
		mov ebx, rest
		mov edi, 0
		cmp edx, 0
		je end1
	rec1 :
		sar eax, 1
		jc rec2
		jnc rec3
		dec edx
		cmp edx, 0
		jg rec1
		jmp end1
	rec2 :
		shl edi, 1
		add edi, 1
		dec edx
		cmp edx, 0
		jg rec1
	rec3 :
		add edi, 1
		dec edx
		cmp edx, 0
		jg rec1

	end1 :
		mov dword ptr[esi], eax
		mov dword ptr[ebx], edi
	}
}
int add() {
	int i = 0;
	int j = 0;
	_asm {
		mov eax, 1000000000000000000
		mov ebx, 1010
		mov ecx, 1000000000000000000
		mov edx, 1010
		add eax, ecx
		adc ebx, edx
		mov i, eax
		mov j, ebx

	}
	cout << bitset<32>(j) << "-" << bitset<32>(i) << endl;
}
int sub() {
	int i = 0;
	int j = 0;
	_asm {
		mov eax, 2
		mov ebx, 1
		mov ecx, 10
		mov edx, 0
		sub eax, ecx
		sbb ebx, edx
		mov i, eax
		mov j, ebx

	}
	cout << bitset<32>(j) << "-" << bitset<32>(i) << endl;
}

unsigned int rotl(unsigned int r, unsigned n) {
	if (n == 0) {
		return r;
	}
	if ((n &= 31) == 0) {
		return n;
	}
	return (r << n) | (r >> (32 - n));
}

unsigned int rotr(unsigned int r, unsigned n) {
	if (n == 0) {
		return r;
	}
	if ((n &= 31) == 0) {
		return n;
	}
	return (r >> n) | (r << (32 - n));
}

int multiplyBy25(int a) {
	_asm {
		mov eax, a
		mov ebx, eax
		mov ecx, eax
		shl eax, 4
		shl ebx, 3
		add eax, ebx
		add eax, ecx
	}
}


short encode_date(short day, short month, short year) {
	_asm {
		mov ax, 0
		mov bx, day
		mov cx, month
		mov dx, year
		or ax, bx
		shl cx, 5
		shl dx, 9
		or ax, cx
		or ax, dx
	}
}

short encode_date1(short day, short month, short year) {
	_asm {
		mov ax, 0
		mov bx, day
		or ax, bx
		shl ax, 4
		mov bx, month
		or ax, bx
		shl ax, 7
		mov bx, year
		or ax, bx
	}
}

void decode_date(short date) {
	const char* format = "day: %d, month: %d, year: %d\n";
	_asm {
		movsx eax, date

		// year
		mov ebx, 1
		shl ebx, 7
		dec ebx
		shl ebx, 9
		and ebx, eax
		shr ebx, 9    // same case as in month
		push ebx

		// month
		mov ebx, 1
		shl ebx, 4
		dec ebx
		shl ebx, 5     // month starts on 6th bit
		and ebx, eax
		shr ebx, 5     // bits has to be pushed back, otherwise it will result in number of 5bits larger
		push ebx

		//day
		mov ebx, 1
		shl ebx, 5		// shifts 1 to 32 
		dec ebx		    // 32-1 = 31 => 11111 (day is coded into 5 bits)
		and ebx, eax	// doing & operation on encoded date number will result in original number because 1's will stay in original position
		push ebx		// push to stack for printf


		push format
		call printf
		add esp, 16
	}
}

struct arm_num {
	unsigned char ror4;
	unsigned char imm8;
};

arm_num* myA = (arm_num*)malloc(sizeof(arm_num));

int arm_encodable(unsigned int n) {
	for (int i = 0; i < 33; i++) {

		int t = rotl(n, i);
		if (((t >> 8) & 0xFFFFFF) == 0) {
			return i + 1;
		}
	}
	return 0;
}

void arm_decode_parts(unsigned short n, struct arm_num* decoded) {
	char a = 0xFF & n;
	char b = (0xF00 & n) >> 8;
	myA->ror4 = b;
	myA->imm8 = a;

}

int zeroExtend32(unsigned char imm) {
	int i = 0;
	i |= imm;
	return i;
}

unsigned int arm_decode(unsigned short n) {
	arm_decode_parts(n, myA);
	return rotr(zeroExtend32(myA->imm8), myA->ror4 * 2);
}

unsigned short arm_encode(unsigned int n) {
	int x = arm_encodable(n);
	if (x != 0) {
		x -= 1;
		unsigned short i = 0;
		i = rotl(n, x);
		short j = (x / 2) << 8;
		return (i | j) & 0xFFF;
	}
}

int main()
{
	cout << "Mask = " << bitset<32>(mask(3, 4)) << endl;
	int* res = (int*)malloc(sizeof(int));
	int* rest = (int*)malloc(sizeof(int));
	cout << divide2(15, 3, res, rest) << endl;
	cout << "resuslt= " << *res << endl;
	cout << "remainder= " << *rest << endl;
	cout << endl;

	add();
	cout << endl;
	sub();

	short date = encode_date(19, 5, 98);
	decode_date(date);

	cout << "rol: " << bitset<32>(rotl(1, 3)) << endl;
	cout << "rol: " << bitset<32>(rotl(1, 31)) << endl;
	cout << "mul25: " << multiplyBy25(5) << endl;

	cout << "encode: " << arm_encode(772) << endl;
	cout << "decode: " << arm_decode(4033) << endl;
	return 0;
}