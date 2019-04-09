#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void factorial_iter(unsigned char a, unsigned long *b)
{
	_asm {
		movsx eax, a
		cmp eax,1
		jl end
		mov ebx, b
		mov ecx, [ebx]
		imul ecx
		mov [ebx], eax
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
	unsigned long ret = 1, *pret = &ret;

	_asm {
		push dword ptr pret
		push dword ptr a
		call factorial_iter
		add esp, 8
	}
	return ret;
}

char *my_strdup(const char* s)
{
	char *x;
	int len;
	_asm {
		push dword ptr s
		call strlen
		pop edx
		mov len, edx
		push eax
		call malloc
		mov x, eax
		add esp, 4

		mov eax, 0
		mov ebx, s
		mov ecx, x
	iter:
		movsx edx, [ebx + eax]
		mov [ecx + eax], edx
		inc eax
		cmp eax, edx
		jl iter
	}
	return x;
}

char *abcs(unsigned char n)
{
	char *x;
	const char *oops =  "Oooops";
	_asm {
		cmp n, 26
		jg end

		movsx eax, n
		push eax
		call malloc
		mov x, eax
		add esp, 4

		mov eax, 0
		mov ebx, 65
		mov ecx, x
		movsx edx, n
	iter:
		mov [ecx + eax], ebx
		inc ebx
		inc eax
		cmp eax, edx
		jl iter
		jmp re

	end:
		mov eax, 6
		push eax
		call malloc
		mov x, eax
		add esp, 4
		push oops
		push x
		call strcpy
		mov x, eax
		add esp, 4
	re:
		
	}
	return x;
}

unsigned int fib(unsigned short n)
{
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

void print_fact(unsigned char n)
{
	char *fmt = "fact(%d) = %d";
	_asm {
		movsx eax, n

		push eax
		call factorial
		add esp, 4
		mov edx, eax


		push edx
		push n
		push fmt
		call printf
	}
	printf("\n");
}

void print_facts(unsigned char n)
{
	_asm {
		cmp n, 0
		jle end
		dec n
		push n
		call print_facts
		add esp, 4
		push n
		call print_fact
		add esp, 4
	end:
	}
}

void read_and_print_fib()
{
	int input;
	const char *format_char = "%d";
	const char *format_string = "%s \n";
	const char *errmess_string = "Wrong argument type";
	_asm {
		mov ebx, input
		mov eax, format_char
		push ebx
		push eax
		call scanf
		add esp, 8
		/*cmp [ebx], 48
		jl errmess
		cmp [ebx], 57
		jg errmess*/
		push[ebx]
		call print_fact
		add esp, 4
		jmp end
	errmess:
		mov eax, format_string
		mov ebx, errmess_string
		push ebx
		push eax
		call printf
		add esp, 8
	end:
	}
}

unsigned int ack(unsigned short m, unsigned short n)
{
	unsigned int res;
	_asm {
		cmp m, 0
		je zeroM
		cmp n, 0
		je zeroN

		movsx eax, n
		dec eax
		push eax
		push m
		call ack
		mov ebx, eax
		add esp, 8

		movsx eax, m
		dec eax
		push ebx
		push eax
		call ack
		mov res, eax
		add esp, 8
		jmp end



	zeroN:
		movsx eax, m
		dec eax
		push 1
		push eax
		call ack
		mov res, eax
		add esp, 8
		jmp end

	zeroM:
		movsx eax, n
		inc eax
		mov res, eax
		jmp end


	end:
	
	}
	return res;
}

unsigned int ackP(unsigned short m, unsigned short n) {
	_asm {
		movsx eax, n
		movsx ebx, m
		cmp ebx, 1
		jl mzer
		jmp mhigh
		mzer :
		inc eax
			jmp end
			mhigh :
		cmp eax, 1
			jl nzer
			dec eax
			push eax
			push ebx
			call ack
			add esp, 8
			dec ebx
			push eax
			push ebx
			call ack
			add esp, 8
			jmp end
			nzer :
		mov eax, 1
			dec ebx
			push eax
			push ebx
			call ack
			add esp, 8
			end:
	}
}

int main()
{

	printf("%u! = %lu\n", 10, factorial(10));
	printf("------------\n");
	printf("%s\n", my_strdup("Hello world!"));
	printf("------------\n");
	printf("%s\n", abcs(20));
	printf("------------\n");
	printf("%d\n", fib(6));
	printf("------------\n");
	print_fact(10);
	printf("------------\n");
	print_facts(10);
	printf("------------\n");
	//read_and_print_fib();
	printf("%d\n", ack(2,1));
	printf("------------\n");
	printf("%d\n", ackP(2, 1));
	system("pause");
	return 0;
}