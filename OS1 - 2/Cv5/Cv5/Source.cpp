#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	pokud predavam hodnotu referenci tak pres []
	int *c
	mov ecx, c
	mov [ecx], eax
*/

/*
	ecx, edx, eax po zavolani fce nejsou chraneny
*/


void factorial_iter(unsigned char a, unsigned long* b)
{
	//if (a <= 1) return;
	//*b *= a;
	//factorial_iter(a - 1, b);
	_asm {
		movsx eax, a
		cmp eax, 1
		jle end

		mov ebx, b
		mov ecx, [ebx]
		imul ecx
		mov[ebx], eax
		dec a

		push dword ptr b
		push dword ptr a
		call factorial_iter
		add esp, 8

	end:
	}
}

unsigned long factorial(unsigned char a)
{
	unsigned long ret = 1, * pret = &ret;

	_asm {
		push dword ptr pret
		push dword ptr a
		call factorial_iter
		add esp, 8
	}
	return ret;
}


char* my_strdup(const char* s) {
	char* x;
	int len;
	_asm {
		push dword ptr s
		call strlen
		pop edx
		add esp, 4
		mov len, edx

		push eax
		call malloc
		mov x, eax
		add esp, 4

		mov eax, 0
		mov ebx, s
		mov ecx, x
	iter :
		movsx edx, [ebx + eax]
		mov[ecx + eax], edx
		inc eax
		cmp eax, edx
		jl iter
	}
	return x;
}

char* abcs(unsigned char n) {
	char* res;
	const char* oops = "Oooops";
	_asm {
		
		cmp n, 26
		jg wrong

		push n
		call malloc
		mov res, eax
		add esp, 4

		mov eax, 0
		mov ebx, 65
		mov ecx, res
		movsx edx, n
	iter:
		mov [ecx + eax], ebx
		inc ebx
		inc eax
		cmp eax, edx
		jl iter
		jmp end

	wrong:
		mov eax, 6
		push eax
		call malloc
		mov res, eax
		add esp, 4

		push oops
		push res
		call strcpy
		mov res, eax
		add esp, 8

	end:	
	}
	return res;
}

unsigned int fib(unsigned short n) {
	_asm {
		cmp n, 1
		jle mensi

		movsx ecx, n
		sub ecx, 1
		push ecx
		call fib
		mov ebx, eax
		add esp, 4

		movsx ecx, n
		sub ecx, 2
		push ecx
		call fib
		add esp, 4

		add eax, ebx

		jmp end

	mensi:
		movsx eax, n
	end:
	}
}

void print_fact(unsigned char n) {
	const char* output = "fact(%d) = %d\n";
	_asm {
		movsx eax, n

		push eax
		call factorial
		add esp, 4

		push eax
		push n
		push output
		call printf
		add esp, 12
	}
}

void print_facts(unsigned char n) {
	_asm {
		mov ebx, 0
		movsx esi, n

		
	iter:
		push ebx
		call print_fact
		add esp, 4

		inc ebx
		cmp ebx, esi
		jle iter
	}
}

void read_and_print_fib() {
	unsigned short* input;
	const char* print_res = "fib(%d) = %d";
	const char* format_char = "%d";
	_asm {
		lea ebx, [input]
		mov eax, dword ptr [format_char]
		push ebx
		push eax
		call scanf
		add esp, 8

		mov ax, word ptr [input]
		push ax
		call fib
		mov edx, eax
		add esp, 4

		push esi
		push [input]
		mov ebx, dword ptr [print_res]
		push ebx
		call printf
		add esp, 12
	}
}

int main() {
	printf("%u! = %lu\n", 10, factorial(10));
	printf("------------\n");
	const char* hello = "Hello world!";
	printf("%s\n", my_strdup(hello));
	printf("------------\n");
	printf("%s\n", abcs(5));
	printf("------------\n");
	printf("%d\n", fib(6));
	printf("------------\n");
	print_fact(10);
	printf("------------\n");
	print_facts(10);
	printf("------------\n");
	read_and_print_fib();
	//printf("%d\n", ack(2, 1));
	//printf("------------\n");
	//printf("%d\n", ackP(2, 1));
	return 0;

}