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
	iter1:
		add eax, 1
		shl eax, 1
		dec edx
		cmp edx, 0
		jg iter1
		add eax, 1
		cmp ebx, 0
		je konec
	iter2:
		shl eax, 1
		dec ebx
		cmp ebx, 0
		jg iter2
	konec:
	}
}

int divide2(int a, int n, int* res, int* rest) {
	_asm {
		mov eax, a
		mov ebx, 1
		mov ecx, n
		shl ebx, cl
		cdq
		idiv ebx

		mov ebx, res
		mov ecx, rest
		mov dword ptr[ebx], eax
		mov dword ptr[ecx], edx
	}
}

int quadWordAdd() {
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
	cout << bitset<32>(j) << bitset<32>(i) << endl;
}
int quadWordSub() {
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
	cout << bitset<32>(j) << bitset<32>(i) << endl;
}

unsigned int rol(unsigned int r, unsigned n) {
	int lastIndex = 1;
	lastIndex = lastIndex << 31;
	for (int i = 0; i < n; i++) {
		int movingBit = 0;
		if (lastIndex & r) {
			movingBit = 1;
		}
		r = r << 1;
		r += movingBit;
	}
	return r;
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

void decode_date(short date) {
	const char* format = "day: %d, month: %d, year: %d\n";
	_asm {
		movsx eax, date

		mov ebx, 1
		shl ebx, 7
		dec ebx
		shl ebx, 9
		and ebx, eax
		shr ebx, 9
		push ebx

		mov ebx, 1
		shl ebx, 4
		dec ebx
		shl ebx, 5
		and ebx, eax
		shr ebx, 5
		push ebx

		mov ebx, 1
		shl ebx, 5
		dec ebx
		and ebx, eax
		push ebx


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
	int i = 0;
	_asm {
		mov eax, n
		mov ecx, 0
	iter1:
		cmp ecx, 32
		je konec2
		mov eax, n
		mov ebx, 0
	iter2:
		rol eax, 1
		inc ebx
		cmp ebx, ecx
		jl iter2
		sar eax, 8
		and eax, 0xFFFFFF
		cmp eax, 0
		je konec1
		inc ecx
		jmp iter1
	konec1:
		mov eax, ecx
		inc eax
		mov i, eax
	konec2:
	}
	return i;
}

void arm_decode_parts(unsigned short n, struct arm_num* decoded) {
	_asm {
		movzx eax, word ptr[n]
		and eax, 0xFF
		mov ecx, dword ptr[myA]
		mov byte ptr[ecx + 1], al
		movzx eax, word ptr[n]
		and eax, 0xF00
		sar eax, 8
		mov ecx, dword ptr[myA]
		mov byte ptr[ecx], al
	}
}

unsigned int arm_decode(unsigned short n) {
	int i = 0;
	_asm {
		mov eax, [myA]
		push eax
		movzx ecx, word ptr[n]
		push ecx
		call arm_decode_parts
		add esp, 8

		mov ecx, dword ptr[myA]
		movzx eax, byte ptr[ecx + 1]
		mov ebx, 0
		mov bl, byte ptr[ecx]

		shl bl, 1
	iter:
		cmp bl, 0
		je konec
		dec bl
		ror eax, 1
		jmp iter
	konec:
		mov i, eax
	}
}

unsigned short arm_encode(unsigned int n) {
	_asm {
		push n
		call arm_encodable
		add esp, 4

		mov ecx, eax
		cmp ecx, 0
		je konec
		dec ecx
		mov eax, n
		mov ebx, 0
	iter1:
		rol eax, 1
		inc ebx
		cmp ebx, ecx
		jl iter1

		shl ecx, 7
		or eax, ecx
		and eax, 0xFFF
	konec:
	}
}

int main()
{
	cout << "Mask = " << bitset<32>(mask(3, 4)) << endl;

	int* res = (int*)malloc(sizeof(int));
	*res = 0;
	int* rest = (int*)malloc(sizeof(int));
	*rest = 0;
	cout << divide2(15, 3, res, rest) << endl;
	cout << "resuslt = " << *res << endl;
	cout << "rest = " << *rest << endl;
	cout << endl;

	quadWordAdd();
	cout << endl;
	quadWordSub();

	short date = encode_date(19, 5, 98);
	decode_date(date);

	cout << "rol: " << bitset<32>(rol(5, 6)) << endl;
	cout << "rol: " << bitset<32>(rol(1, 29)) << endl;
	cout << "mul25: " << multiplyBy25(1) << endl;

	cout << "encode: " << arm_encode(42) << endl;
	cout << "decode: " << arm_decode(666) << endl;
	return 0;
}