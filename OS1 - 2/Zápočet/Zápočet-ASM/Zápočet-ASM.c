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

		push edi
		call canvas_print
		add esp, 4

		push 13
		push 2
		push 3
		push edi
		call canvas_hline
		add esp, 16
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
		movsx edi, byte ptr [edi]

		mov [ebp + 128], 0
	compare:
		mov eax, edi
		and eax, 11000000b
		rol edi, 2
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
	}
}

//Funkce pro vykreslení vodorovné čáry, fungují na principu počítání počátečních a koncových bodů, kontrola překročení plátna je zajištěna
//kontrolou kolik bitů je možno zpracovat, než dojde k vyskočení z plátna
void canvas_hline(struct canvas* canvas, unsigned int x, unsigned int y, int length) {
	const char* format = "%d\n";
	const char* cycle = "start: %d end: %d\n";
	_asm {
		cmp[ebp + 12], 0
		jle konec
		cmp[ebp + 16], 0
		jle konec
		mov eax, [ebp + 8]
		mov ebx, [eax]
		cmp[ebp + 12], ebx
		jge konec
		mov ebx, [eax + 4]
		jge konec

		mov [ebp + 128], 1			//preBits
		mov [ebp + 132], 1			//postBits

		cmp[ebp + 20], 0
		je konec
		jl zapornaDelka

		mov [ebp + 136], 0			//bitsManipulated
		mov [ebp + 140], 0			//offset

		mov eax, dword ptr[ebp + 8]
		movsx eax, [eax + 4]
		shl eax, 1
		mov [ebp + 144], eax		//Počet bitů na řádku
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
		mov ecx, eax				//localStartBit

		mov eax, ebx
		mov edx, 8
		mul edx
		mov edx, eax
		add edx, 7					//localEndBit

		mov eax, ebx
		inc eax
		mul [ebp + 144]
		cmp eax, esi
		jle skipped
		cmp [ebp + 140], 0
		jne skipped

		mov eax, ebx
		mul [ebp + 144]
		mov [ebp + 140], esi
		sub [ebp + 140], eax

		push [ebp + 140]
		push format
		call printf
		add esp, 8


	skipped:

		//push edx
		//push ecx
		//push cycle
		//call printf
		//add esp, 12

		inc ebx
		jmp iter

	zapornaDelka:

	konec:
	}
	//if (x < 0 || y < 0 || x > canvas->width || y > canvas->height)
	//	return;

	//int bitsOnLine = canvas->width * 2;
	//int preBits = 1;
	//int postBits = 1;
	////Vykreslení vodorovné čáry pro velikost větší než 0
	////Spočítání počátečního a koncového bitu, který leží na čáře
	//if (length > 0) {
	//	int startBit = y * bitsOnLine;
	//	startBit += (2 * x);
	//	int endBit = startBit + (length * 2);
	//	int bitsManipulated = 0;
	//	int offset = 0;
	//	for (int i = 0; i < canvas->size; i++) {
	//		int localStartBit = i * 8;
	//		int localEndBit = i * 8 + 7;
	//		//Spočítá se, kolik bitů je možno změnit, tak, aby nedošlo k překročení hranice
	//		if ((i + 1) * bitsOnLine > startBit && !offset)
	//			offset = startBit - (i * bitsOnLine);
	//		//Pokud začátek neleží na začátku bytu, spočítá se offset začátku v rámci bytu, a do postupně se rotuje dokud se byte nevrátí do původního stavu
	//		if (localStartBit <= startBit && startBit <= localEndBit && preBits) {
	//			int bitsToRotate = startBit - localStartBit;
	//			for (int j = bitsToRotate; j < 8; j += 2) {
	//				canvas->mask[i] = canvas->mask[i] << 2;
	//				canvas->mask[i] |= 0b00000010;
	//				bitsManipulated += 2;
	//			}
	//			preBits = 0;
	//		}
	//		//Rotují se kopletní byty
	//		if (startBit <= i * 8 && endBit > i * 8 + 7) {
	//			canvas->mask[i] |= 0b10101010;
	//			bitsManipulated += 8;
	//		}
	//		//Pokud konec úsečky není zarovnán s koncem bytu, provádí se její dokreslení
	//		if (localStartBit <= endBit && endBit <= localEndBit && postBits) {
	//			int bitsToRotate = endBit - localStartBit;
	//			for (int j = 8 - bitsToRotate; j < 8; j += 2) {
	//				canvas->mask[i] |= 0b00000010;
	//				canvas->mask[i] = rotr(canvas->mask[i], 2);
	//				bitsManipulated += 2;
	//			}
	//			postBits = 0;
	//		}
	//		if (bitsManipulated >= (bitsOnLine - offset))
	//			return;
	//	}
	//}
	//else if (length < 0) {
	//	int startBit = y * bitsOnLine;
	//	startBit += (2 * x + 2);
	//	int endBit = startBit;

	//	int col = endBit / bitsOnLine;
	//	int colStartBit = col * bitsOnLine;
	//	startBit += (2 * length + 2);

	//	//Pokud by při použití délky došlo k překročení hranice, tak se jako počáteční bit použije začítek řádku
	//	if (startBit < colStartBit)
	//		startBit = colStartBit;

	//	for (int i = 0; i < canvas->size; i++) {
	//		int localStartBit = i * 8;
	//		int localEndBit = i * 8 + 7;
	//		//Opět se provádí rotace ve třech částech, pro nezarovnané konce a začáty bytů, a pro celé byty
	//		if (localStartBit <= startBit && startBit <= localEndBit && preBits) {
	//			int bitsToRotate = startBit - localStartBit;
	//			canvas->mask[i] = rotr(canvas->mask[i], bitsToRotate);
	//			for (int j = bitsToRotate; j <= 8; j += 2) {
	//				canvas->mask[i] |= 0b00000010;
	//				canvas->mask[i] = rotr(canvas->mask[i], 2);
	//			}
	//			preBits = 0;
	//		}
	//		if (startBit <= i * 8 && endBit > i * 8 + 7) {
	//			canvas->mask[i] |= 0b10101010;
	//		}
	//		if (localStartBit <= endBit && endBit <= localEndBit && postBits) {
	//			int bitsToRotate = endBit - localStartBit;
	//			for (int j = 8 - bitsToRotate; j < 8; j += 2) {
	//				canvas->mask[i] |= 0b00000010;
	//				canvas->mask[i] = rotr(canvas->mask[i], 2);
	//			}
	//			postBits = 0;
	//		}
	//	}
	//}
}

//Funkce pro vykreslování vertikálních čar, spočítá se počáteční bit, a poté se přičítá počet bitů potřebných k posunu na další řádek
//Funce pracují na principu hledání bytu ve kterém se nachází patřičný bod, a následnému přičítání počtu bitů potřebných k dosažení dalšího bitu
void canvas_vline(struct canvas* canvas, unsigned int x, unsigned int y, int length) {
	_asm {
		cmp[ebp + 12], 0
		jle konec
		cmp[ebp + 16], 0
		jle konec
		mov eax, [ebp + 8]
		mov ebx, [eax]
		cmp[ebp + 12], ebx
		jle konec
		mov ebx, [eax + 4]
		jle konec




	konec:
	}
	//if (x < 0 || y < 0 || x > canvas->width || y > canvas->height)
	//	return;

	//int bitsToNextLine = canvas->width * 2;
	//if (length > 0) {
	//	int startBit = y * bitsToNextLine;
	//	startBit += 2 * x + 2;
	//	int endBit = startBit + length * bitsToNextLine;
	//	int nextBitToRotate = startBit;
	//	int rotationFlag = 1;
	//	int postBits = 1;
	//	int rotation = 0;
	//	for (int i = 0; i < canvas->size; i++) {
	//		int localStartBit = i * 8;
	//		int localEndBit = i * 8 + 7;
	//		if (nextBitToRotate <= localEndBit && localEndBit <= endBit) {
	//			if (rotationFlag) {
	//				rotation = localStartBit - startBit;
	//				rotationFlag = 0;
	//			}
	//			canvas->mask[i] = rotr(canvas->mask[i], rotation);
	//			canvas->mask[i] |= 0b00000001;
	//			canvas->mask[i] = rotr(canvas->mask[i], 8 - rotation - 1);
	//			nextBitToRotate += bitsToNextLine;
	//			//Podmínka pro ukončení funce, dojde-li k překročení hranice plátna
	//			if (nextBitToRotate > canvas->width* canvas->height * 2) {
	//				return;
	//			}
	//		}
	//	}
	//}
	//else if (length < 0) {
	//	int endBit = y * bitsToNextLine;
	//	endBit += 2 * x + 2;
	//	int startBit = endBit + (length + 1) * bitsToNextLine;
	//	int nextBitToRotate = startBit;
	//	int rotationFlag = 1;
	//	int postBits = 1;
	//	int rotation = 0;
	//	for (int i = 0; i < canvas->size; i++) {
	//		int localStartBit = i * 8;
	//		int localEndBit = i * 8 + 7;
	//		if (nextBitToRotate <= localEndBit && nextBitToRotate <= endBit) {
	//			if (rotationFlag) {
	//				rotation = startBit - localStartBit;
	//				rotationFlag = 0;
	//			}
	//			canvas->mask[i] = rotr(canvas->mask[i], 8 - rotation);
	//			canvas->mask[i] |= 0b00000001;
	//			canvas->mask[i] = rotr(canvas->mask[i], rotation);
	//			nextBitToRotate += bitsToNextLine;
	//			//Dojde-li k překročení hranice, další bod by měl zápornou pozici
	//			if (nextBitToRotate < 0) {
	//				return;
	//			}
	//		}
	//	}
	//}
}