#include <iostream>
using namespace std;

int avg(unsigned short a, char b, int c, int* result) {
    _asm {
        movzx eax, a
        movsx ebx, b
        add eax, ebx
        add eax, c

        mov ecx, 3
        cdq
        idiv ecx
        mov ebx, [result]
        mov ebx, eax
    }
}

int main()
{
    int* result = 0;
    unsigned short a = 5;
    char b = 10;
    int c = 20;
    int res = avg(5, 10, 20, result);

    cout << res << endl;
    cout << result << endl;
    cout << "Hello World!\n";
}