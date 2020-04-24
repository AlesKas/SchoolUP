#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
    dostanu pointer/pole jako argument ->
    mov eax, arg
    mov [eax], neco - zapis
    mov ebx, [eax] - cteni
*/

void avg(unsigned short a, char b, int c, int* result) {
    _asm {
        movzx eax, a
        movsx ebx, b
        add eax, ebx
        add eax, c

        mov ecx, 3
        cdq
        idiv ecx
        mov ebx, result
        mov [ebx], eax
    }
}

void dupdup(char* dest, char* src) {
    const char* prin = "%c\n";
    _asm {
        mov esi, src
        mov edi, dest
        mov ebx, 0
        mov ecx, 0

    foo:
        cmp [edi + ebx], 0x00
        je bar
        mov al, [esi + ebx]
        
        mov [edi + ecx], al
        mov [edi + 1 + ecx], al
        inc ebx
        add ecx, 2
        jmp foo

    bar:
    }
}

int trueword(short* a) {
    const char* prin = "%d";
    _asm {
        movsx ebx, a
        mov ecx, [a]

        cmp ebx, 0
        je falseend
        cmp ecx, 0
        je falseend
        mov eax, 1
        jmp endend

    falseend:
        mov eax, 0
    endend:
    }
}

void nasobky(int n, int k) {
    const char* prin = "%d ";
    _asm {
        mov esi, n
        mov edi, k
        mov ebx, 1

    foo:
        cmp ebx, esi
        jg endend

        push edi
        push prin
        call printf
        add esp, 8
        add edi, k
        inc ebx
        jmp foo

    endend:
    }
}

int main()
{
    int result = 0;
    unsigned short a = 5;
    char b = 10;
    int c = 20;
    avg(5, 10, 20, &result);
    printf("%d\n", result);

    char* src = "abcd";
    char* dest = (char*)malloc(sizeof(char) * 8);
    dupdup(dest, src);
    printf("%s\n", dest);

    short* aa = 0;
    printf("%d\n", trueword(aa));

    nasobky(5, 5);

    return 0;
}