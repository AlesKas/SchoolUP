#include <stdio.h>
#include <stdlib.h>

//Informace o bodu jsou uloženy ve dvou bitech
//První bit odpovídá informaci o horizontální čáře - 0 nepřítomna, 1 přítomna
//Druhý bit odpovídá informaci o vertikální čáře - 0 nepřítomna, 1 přítomna
struct canvas {
	int width;		//[eax]
	int height;		//[eax+4]
	int size;		//[eax+8]
	char* mask;		//[eax+12]
};

//Pomocná funkce pro rotaci bitů doprava
unsigned int rotr(char num, unsigned int rotation)
{
	rotation %= 7;

	while (rotation--)
		num = ((num >> 1)& (~(1 << 7)) | ((num & 1) << 7));

	return num;
}

struct canvas* canvas_create(int width, int height);
void canvas_init(struct canvas* canvas);
void canvas_free(struct canvas* canvas);
void canvas_print(struct canvas* canvas);
void canvas_hline(struct canvas* canvas, unsigned int x, unsigned int y, int length);
void canvas_vline(struct canvas* canvas, unsigned int x, unsigned int y, int length);

//Nelze vykreslovacím funkcím zadat záporné hodnoty, nebo hodnoty, které jsou větší než zvolená velikost plátna
int main() {
	const char* format = "height: %d width: %d size:%d mask:%d\n";
	struct canvas* c;
	_asm {
		push 10
		push 20
		call canvas_create
		add esp, 8
		mov edi, eax
		mov [c], eax

		push dword ptr [edi +12]
		push dword ptr [edi +8]
		push dword ptr [edi +4]
		push dword ptr [edi]
		push format
		call printf
		add esp, 20

		push 13
		push 2
		push 3
		push edi
		call canvas_hline
		add esp, 16

		push -12
		push 5
		push 14
		push edi
		call canvas_hline
		add esp, 16

		push 6
		push 1
		push 4
		push edi
		call canvas_vline
		add esp, 16

		push edi
		call canvas_print
		add esp, 4
	}

	int lines = 0;
	printf("\n");
	for (int i = 0; i < c->size; i++) {
		printf("%d", c->mask[i]);
		lines++;
		if (lines == 10) {
			printf("\n");
			lines = 0;
		}
	}
	//struct canvas* c = canvas_create(20, 10);
	//canvas_hline(c, 3, 2, 13);
	//canvas_hline(c, 14, 5, -11);
	//canvas_vline(c, 4, 1, 6);
	//canvas_vline(c, 14, 6, -6);
	//canvas_vline(c, 9, 5, 20);
	//canvas_print(c);
	//canvas_free(c);
	return 0;
}

struct canvas* canvas_create(int width, int height) {
	_asm {

		mov eax,dword ptr [ebp + 8]
		mov ebx, dword ptr[ebp + 12]
		mov edx, 0
		cdq
		mul ebx
		mov ebx, 8
		div ebx
		shl eax, 1
		mov esi, eax //Registr bezpečný pro volání funkcí

		push esi
		call malloc
		add esp, 4
		mov edi, eax

		push dword ptr 16
		call malloc
		add esp, 4

		mov ebx, eax

		mov ecx, [ebp + 8]
		mov edx, [ebp + 12]

		mov dword ptr[eax], edx
		mov dword ptr[eax + 4], ecx
		mov dword ptr[eax + 8], esi
		mov dword ptr[eax + 12], edi

		push eax
		call canvas_init
		add esp, 4
	}
}

//Inicializace plátna, na začátku je plátno bílé
void canvas_init(struct canvas* canvas) {
	_asm {
		mov eax, [ebp + 8]
		mov ecx, [eax + 8]
		mov edx, [eax + 12]
	while:
		mov byte ptr [edx + ecx], 00000000b
		loop while
		mov[edx], 00000000b
		mov dword ptr[eax + 12], edx

	}
}

//Funcke pro uvolnění plátna z paměti
void canvas_free(struct canvas* canvas) {
	_asm {
		mov eax, [ebp + 8]
		mov eax, [eax + 12]
		push eax
		call free
		add esp, 4

		mov eax, [ebp + 8]
		push eax
		call free
		add esp, 4
	}
	free(canvas->mask);
	free(canvas);
}

//Funce pro tisk plátna, prochází se jednotlivé dvoubity, a zjišťuje se, je-li
//přítomná svislá nebo vodorovná čára
void canvas_print(struct canvas* canvas) {
	const char* nothingSymbol = ".";
	const char* bothSymbol = "+";
	const char* horizontalSymbol = "-";
	const char* verticalSymbol = "|";
	const char* newLine = "\n";
	_asm {
		mov esi, 0			//linesWritten
		mov ebx, 0			//size
	
	iter: 
		mov edi, dword ptr [ebp + 8]
		mov edi, dword ptr [edi + 12]
		movsx edi, byte ptr [edi + ebx]

		mov [ebp + 128], 0
	compare:
		mov eax, edi
		and eax, 11000000b
		shl edi, 2
		inc [ebp + 128]
		
		cmp eax, 00000000b
		je nothing
		cmp eax, 11000000b
		je both
		cmp eax, 01000000b
		je vertical
		cmp eax, 10000000b
		je horizontal

	returned:
		cmp [ebp + 128], 4
		je resume
		jmp compare

	horizontal:
		push horizontalSymbol
		call printf
		add esp, 4
		jmp endline

	vertical:
		push verticalSymbol
		call printf
		add esp, 4
		jmp endline

	both:
		push bothSymbol
		call printf
		add esp, 4
		jmp endline

	nothing:
		push nothingSymbol
		call printf
		add esp, 4
		jmp endline
	back:
		jmp returned


	resume:
		inc ebx
		mov edi, [ebp + 8]
		mov edi, dword ptr [edi + 8]
		cmp ebx, edi
		je konec
		jmp iter

	endline:
		inc esi
		mov eax, [ebp + 8]
		mov eax, [eax + 4]
		cmp esi, eax
		jl returned

		mov esi, 0
		push newLine
		call printf
		add esp, 4
		jmp returned
	konec:
		push newLine
		call printf
		add esp, 4
	}
}

//Funkce pro vykreslení vodorovné čáry, fungují na principu počítání počátečních a koncových bodů, kontrola překročení plátna je zajištěna
//kontrolou kolik bitů je možno zpracovat, než dojde k vyskočení z plátna
void canvas_hline(struct canvas* canvas, unsigned int x, unsigned int y, int length) {
	_asm {
		cmp[ebp + 12], 0
		jle konec
		cmp[ebp + 16], 0
		jle konec
		mov eax, [ebp + 4]
		mov ebx, [eax]
		cmp[ebp + 12], ebx
		jge konec
		mov ebx, [eax + 4]
		jge konec

		mov [ebp + 128], 1			//preBits
		mov [ebp + 132], 1			//postBits
		mov eax, dword ptr[ebp + 8]
		movsx eax, [eax + 4]
		shl eax, 1
		mov[ebp + 144], eax			//Počet bitů na řádku

		mov eax, [ebp +20]
		cmp eax, 0
		je konec
		jl zapornaDelka

		mov [ebp + 136], 0			//bitsManipulated
		mov [ebp + 140], 0			//offset

		mov eax, [ebp + 144]
		mul[ebp + 16]
		mov esi, eax				//V esi se nachází startovní bit
		mov eax, [ebp + 12]
		shl eax, 1
		add esi, eax

		mov eax, [ebp + 20]
		shl eax, 1
		add eax, esi
		mov edi, eax				//V edi je koncový bit

		mov ebx, 0
	iter:
		mov eax, [ebp + 8]
		mov eax, [eax + 8]
		cmp ebx, eax
		je konec

		mov eax, ebx
		mov ecx, 8
		mul ecx
		mov [ebp + 148], eax				//localStartBit

		mov eax, ebx
		mov edx, 8
		mul edx
		mov edx, eax
		add edx, 7
		mov [ebp + 152], edx				//localEndBit

		mov eax, ebx
		inc eax
		mov ecx, [ebp + 144]
		mul[ebp + 144]
		cmp eax, esi
		jle skipped
		cmp [ebp + 140], 0
		jne skipped

		mov eax, ebx
		mov ecx, [ebp + 144]
		mul ecx
		mov edx, esi
		sub edx, eax
		mov [ebp + 140], edx

	skipped:

		mov eax, [ebp + 148]
		cmp[ebp + 148], esi
		jg skippedPre
		mov eax, [ebp + 152]
		cmp esi, eax
		jg skippedPre
		mov eax, [ebp + 128]
		cmp eax, 1
		jg skippedPre

		mov eax, esi
		sub eax, [ebp + 148]

	preIter:

		cmp eax, 8
		jge skippedPre

		mov edx, [ebp + 8]
		mov edx, [edx + 12]

		mov ecx, [edx + ebx]
		ror ecx, 2
		or ecx, 00000010b
		mov [edx + ebx], ecx

		add [ebp + 136], 2
		mov [ebp + 128], 0

		add eax, 2
		jmp preIter
	skippedPre:
	
		mov eax, ebx
		mov edx, 8
		mul edx
		mov ecx, eax

		mov eax, ebx
		mov edx, 8
		mul edx
		add eax, 7
		mov edx, eax

		cmp esi, ecx
		jg skippedMain
		cmp edi, edx
		jle skippedMain

		mov edx, [ebp + 8]
		mov edx, [edx + 12]
		mov edx, [edx + ebx]
		or edx, 10101010b
		mov eax, [ebp + 8]
		mov eax, [ebp + 8]
		mov eax, [eax + 12]
		mov [eax + ebx], edx
		mov eax, edx
		mov eax, [ebp + 136]
		add eax, 8
		mov [ebp + 136], eax

	skippedMain:

		cmp [ebp + 148], edi
		jg skippedPost
		cmp edi, [ebp + 152]
		jg skippedPost
		cmp [ebp + 132], 0
		je skippedPost

		mov eax, edi
		mov ecx, [ebp + 148]
		sub eax, ecx
		mov ecx, 8
		sub ecx, eax
	postIter:
		cmp ecx, 8
		jge skippedPost
		mov eax, [ebp + 8]
		mov eax, [eax + 12]
		mov edx, [eax + ebx]
		ror edx, 2
		or edx, 10000000b
		mov [eax + ebx], edx
		add [ebp + 136], 2
	skippedPost:

		mov eax, [ebp + 136]
		mov ecx, [ebp + 144]
		mov edx, [ebp + 140]
		sub ecx, edx
		cmp eax, ecx
		jge konec

		inc ebx
		jmp iter

	zapornaDelka:
		mov eax, [ebp + 16]
		mov ebx, [ebp + 144]
		mul ebx
		mov ebx, [ebp + 12]
		shl ebx, 1
		add ebx, 2
		add eax, ebx
		mov edi, eax			//Koncový bit

		mov ebx, [ebp + 20]
		shl ebx, 1
		add ebx, 4
		add eax, ebx
		mov esi, eax			//Začáteční bit

		mov eax, edi
		mov ebx, [ebp + 144]
		mov edx, 0
		cdq
		div ebx

		mov ebx, [ebp + 144]
		mul ebx
		
		cmp esi, eax
		jge sizegood
		mov esi, eax

	sizegood:
		mov ebx, 0
	iterZaporny:
		mov eax, [ebp + 8]
		mov eax, [eax + 8]
		cmp ebx, eax
		jge konec

		mov eax, ebx
		mov ecx, 8
		mul ecx
		mov[ebp + 148], eax				//localStartBit

		mov eax, ebx
		mov edx, 8
		mul edx
		mov edx, eax
		add edx, 7
		mov[ebp + 152], edx				//localEndBit

		mov eax, [ebp + 148]
		cmp eax, esi
		jg skippedPreZaporne
		mov eax, [ebp + 152]
		cmp esi, eax
		jg skippedPreZaporne
		mov eax, [ebp + 128]
		cmp eax, 1
		jg skippedPreZaporne

		mov eax, esi
		mov ecx, [ebp + 148]
		mov edx, [ebp + 152]
		sub eax, ecx
		mov [ebp + 156], eax

		mov ecx,  [ebp + 8]
		mov ecx, [ecx + 12]
		mov edx, [ecx + ebx]

		push eax
		push edx
		call rotr
		add esp, 8

		mov ecx, [ebp + 8]
		mov ecx, [ecx + 12]
		mov [ecx + ebx], eax

		mov eax, [ebp + 156]
	innerIter:
		cmp eax, 8
		jg skippedPreZaporne

		mov ecx, [ebp + 8]
		mov ecx, [ecx + 12]
		mov edx, [ecx + ebx]

		rol edx, 2
		or edx, 00000010b

		mov ecx, [ebp + 8]
		mov ecx, [ecx + 12]
		mov [ecx + ebx], edx

		mov eax, [ebp + 156]
		add eax, 2

		mov[ebp + 128], 0
		mov [ebp + 156], eax
		jmp innerIter
	skippedPreZaporne:

		mov eax, ebx
		mov edx, 8
		mul edx
		mov ecx, eax

		mov eax, ebx
		mov edx, 8
		mul edx
		add eax, 7
		mov edx, eax

		cmp esi, ecx
		jg skippedMainZaporny
		cmp edi, edx
		jle skippedMainZaporny

		mov edx, [ebp + 8]
		mov edx, [edx + 12]
		mov edx, [edx + ebx]
		or edx, 10101010b
		mov eax, [ebp + 8]
		mov eax, [ebp + 8]
		mov eax, [eax + 12]
		mov[eax + ebx], edx
		mov eax, edx
		mov eax, [ebp + 136]
		add eax, 8
		mov[ebp + 136], eax

	skippedMainZaporny:

		cmp[ebp + 148], edi
		jg skippedPostZaporny
		cmp edi, [ebp + 152]
		jg skippedPostZaporny
		cmp[ebp + 132], 0
		je skippedPostZaporny

		mov eax, edi
		mov ecx, [ebp + 148]
		sub eax, ecx
		mov ecx, 8
		sub ecx, eax
	postIterZaporny:
		cmp ecx, 8
		jge skippedPostZaporny
		mov eax, [ebp + 8]
		mov eax, [eax + 12]
		mov edx, [eax + ebx]
		ror edx, 2
		or edx, 10000000b
		mov[eax + ebx], edx
		add ecx, 2
		jmp postIterZaporny

	skippedPostZaporny:

		inc ebx
		jmp iterZaporny

	konec:
	}
}

//Funkce pro vykreslování vertikálních čar, spočítá se počáteční bit, a poté se přičítá počet bitů potřebných k posunu na další řádek
//Funce pracují na principu hledání bytu ve kterém se nachází patřičný bod, a následnému přičítání počtu bitů potřebných k dosažení dalšího bitu
void canvas_vline(struct canvas* canvas, unsigned int x, unsigned int y, int length) {
	const char* format = "%d\n";
	const char* cycle = "start: %d end: %d\n";
	_asm {

		cmp[ebp + 12], 0
		jle konec
		cmp[ebp + 16], 0
		jle konec
		mov eax, [ebp + 4]
		mov ebx, [eax]
		cmp[ebp + 12], ebx
		jge konec
		mov ebx, [eax + 4]
		jge konec

		mov eax, [ebp + 8]
		mov ebx, [eax + 4]
		shl ebx, 1
		mov[ebp + 144], ebx			//Počet bitů na řádku

		cmp [ebp + 20], 0
		jl zapornaVertikalni

		mov eax, [ebp + 16]
		mov ebx, [ebp + 144]
		mul ebx
		mov ebx, eax
		mov eax, [ebp + 12]
		shl eax, 1
		add eax, 2
		add ebx, eax
		mov esi, ebx

		mov eax, [ebp + 144]
		mov ebx, [ebp + 20]
		mul ebx
		add eax, esi
		mov edi, eax

		push edi
		push esi
		push cycle
		call printf
		add esp, 12 


	zapornaVertikalni:

	konec:
	}
}