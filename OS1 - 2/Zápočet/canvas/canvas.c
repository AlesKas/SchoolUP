#include <stdio.h>
#include <stdlib.h>

//Informace o bodu jsou uloženy ve dvou bitech
//První bit odpovídá informaci o horizontální čáře - 0 nepřítomna, 1 přítomna
//Druhý bit odpovídá informaci o vertikální čáře - 0 nepřítomna, 1 přítomna

struct canvas {
	char* mask;
	int width;
	int height;
	int size;
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
	struct canvas* c = canvas_create(20, 10);
	canvas_hline(c, 3, 2, 13);
	canvas_hline(c, 14, 5, -11);
	canvas_vline(c, 4, 1, 20);
	canvas_vline(c, 14, 6, -9);
	canvas_vline(c, 9, 5, 20);
	canvas_print(c);
	canvas_free(c);
	return 0;
}

struct canvas* canvas_create(int width, int height){
	int size = (width * height) * 2;
	size /= 8;
	struct canvas* temp = malloc(sizeof(struct canvas));
	temp->mask = malloc(size);
	temp->height = height;
	temp->width = width;
	temp->size = size;
	canvas_init(temp);
	return temp;
}

//Inicializace plátna, na začátku je plátno bílé
void canvas_init(struct canvas* canvas) {
	for (int i = 0; i < canvas->size; i++) {
		canvas->mask[i] = 0b00000000;
	}
}

//Funcke pro uvolnění plátna z paměti
void canvas_free(struct canvas* canvas) {
	free(canvas->mask);
	free(canvas);
}

//Funce pro tisk plátna, prochází se jednotlivé dvoubity, a zjišťuje se, je-li
//přítomná svislá nebo vodorovná čára
void canvas_print(struct canvas* canvas) {
	int linesWritten = 0;
	char mask = 0b11000000;
	for (int i = 0; i < canvas->size; i++) {
		char item = canvas->mask[i];
		for (int j = 0; j < 8; j += 2) {
			int location = item & mask;
			item = item << 2;

			if (!location)					//0b00000000
				printf(".");
			else if (!(location ^ -64))		//0b11000000
				printf("+");
			else if (!(location ^ -128))	//0b10000000
				printf("-");
			else							//0b01000000
				printf("|");

			linesWritten++;
			if (linesWritten == canvas->width)
			{
				printf("\n");
				linesWritten = 0;
			}
		}
	}
}

//Funkce pro vykreslení vodorovné čáry, fungují na principu počítání počátečních a koncových bodů, kontrola překročení plátna je zajištěna
//kontrolou kolik bitů je možno zpracovat, než dojde k vyskočení z plátna
void canvas_hline(struct canvas* canvas, unsigned int x, unsigned int y, int length) {
	if (x < 0 || y < 0 || x > canvas->width || y > canvas->height)
		return;

	int bitsOnLine = canvas->width * 2;
	int preBits = 1;
	int postBits = 1;
	//Vykreslení vodorovné čáry pro velikost větší než 0
	//Spočítání počátečního a koncového bitu, který leží na čáře
	if (length > 0) {
		int startBit = y * bitsOnLine;
		startBit += (2 * x);
		int endBit = startBit + (length * 2);
		int bitsManipulated = 0;
		int offset = 0;
		for (int i = 0; i < canvas->size; i++) {
			int localStartBit = i * 8;
			int localEndBit = i * 8 + 7;
			//Spočítá se, kolik bitů je možno změnit, tak, aby nedošlo k překročení hranice
			if ((i + 1) * bitsOnLine > startBit && !offset)
				offset = startBit - (i * bitsOnLine);
			//Pokud začátek neleží na začátku bytu, spočítá se offset začátku v rámci bytu, a do postupně se rotuje dokud se byte nevrátí do původního stavu
			if (localStartBit <= startBit && startBit <= localEndBit && preBits) {
				int bitsToRotate = startBit - localStartBit;
				for (int j = bitsToRotate; j < 8; j += 2) {
					canvas->mask[i] = canvas->mask[i] << 2;
					canvas->mask[i] |= 0b00000010;
					bitsManipulated += 2;
				}
				preBits = 0;
			}
			//Rotují se kopletní byty
			if (startBit <= i * 8 && endBit > i * 8 + 7) {
				canvas->mask[i] |= 0b10101010;
				bitsManipulated += 8;
			}
			//Pokud konec úsečky není zarovnán s koncem bytu, provádí se její dokreslení
			if (localStartBit <= endBit && endBit <= localEndBit && postBits) {
				int bitsToRotate = endBit - localStartBit;
				for (int j = 8 - bitsToRotate; j < 8; j += 2) {
					canvas->mask[i] |= 0b00000010;
					canvas->mask[i] = rotr(canvas->mask[i], 2);
					bitsManipulated += 2;
				}
				postBits = 0;
			}
			if (bitsManipulated >= (bitsOnLine - offset))
				return;
		}
	}
	else if (length < 0) {
		int startBit = y * bitsOnLine;
		startBit += (2 * x + 2);
		int endBit = startBit;

		int col = endBit / bitsOnLine;
		int colStartBit = col * bitsOnLine;
		startBit += (2 * length + 2);

		//Pokud by při použití délky došlo k překročení hranice, tak se jako počáteční bit použije začítek řádku
		if (startBit < colStartBit)
			startBit = colStartBit;

		for (int i = 0; i < canvas->size; i++) {
			int localStartBit = i * 8;
			int localEndBit = i * 8 + 7;
			//Opět se provádí rotace ve třech částech, pro nezarovnané konce a začáty bytů, a pro celé byty
			if (localStartBit <= startBit && startBit <= localEndBit && preBits) {
				int bitsToRotate = startBit - localStartBit;
				canvas->mask[i] = rotr(canvas->mask[i], bitsToRotate);
				for (int j = bitsToRotate; j <= 8; j+=2) {
					canvas->mask[i] |= 0b00000010;
					canvas->mask[i] = rotr(canvas->mask[i], 2);
				}
				preBits = 0;
			}
			if (startBit <= i * 8 && endBit > i * 8 + 7) {
				canvas->mask[i] |= 0b10101010;
			}
			if (localStartBit <= endBit && endBit <= localEndBit && postBits) {
				int bitsToRotate = endBit - localStartBit;
				for (int j = 8 - bitsToRotate; j < 8; j += 2) {
					canvas->mask[i] |= 0b00000010;
					canvas->mask[i] = rotr(canvas->mask[i], 2);
				}
				postBits = 0;
			}
		}		
	}
}

//Funkce pro vykreslování vertikálních čar, spočítá se počáteční bit, a poté se přičítá počet bitů potřebných k posunu na další řádek
//Funce pracují na principu hledání bytu ve kterém se nachází patřičný bod, a následnému přičítání počtu bitů potřebných k dosažení dalšího bitu
void canvas_vline(struct canvas* canvas, unsigned int x, unsigned int y, int length) {
	if (x < 0 || y < 0 || x > canvas->width || y > canvas->height)
		return;

	int bitsToNextLine = canvas->width * 2;
	if (length > 0) {
		int startBit = y * bitsToNextLine;
		startBit += 2 * x + 2;
		int endBit = startBit + length * bitsToNextLine;
		int nextBitToRotate = startBit;
		int rotationFlag = 1;
		int postBits = 1;
		int rotation = 0;
		for (int i = 0; i < canvas->size; i++) {
			int localStartBit = i * 8;
			int localEndBit = i * 8 + 7;
			if (nextBitToRotate <= localEndBit && localEndBit <= endBit) {
				if (rotationFlag) {
					rotation = localStartBit - startBit;
					rotationFlag = 0;
				}
				canvas->mask[i] = rotr(canvas->mask[i], rotation);
				canvas->mask[i] |= 0b00000001;
				canvas->mask[i] = rotr(canvas->mask[i], 8 - rotation - 1);
				nextBitToRotate += bitsToNextLine;
				//Podmínka pro ukončení funce, dojde-li k překročení hranice plátna
				if (nextBitToRotate > canvas->width* canvas->height * 2) {
					return;
				}
			}
		}
	}
	else if (length < 0) {
		int endBit = y * bitsToNextLine;
		endBit += 2 * x + 2;
		int startBit = endBit + (length + 1) * bitsToNextLine;
		//Pokud se překročí velikost plátna, má startovní bit zápornou souřadnici
		//a přičítá se počet bitů do dalšího řádku, dokud se nenarazí na první kladný, a ten představuje nový start
		while (startBit < 0) {
			startBit += bitsToNextLine;
		}
		int nextBitToRotate = startBit;
		int rotationFlag = 1;
		int postBits = 1;
		int rotation = 0;
		for (int i = 0; i < canvas->size; i++) {
			int localStartBit = i * 8;
			int localEndBit = i * 8 + 7;
			if (nextBitToRotate <= localEndBit && nextBitToRotate <= endBit) {
				if (rotationFlag) {
					rotation = startBit - localStartBit;
					rotationFlag = 0;
				}
				canvas->mask[i] = rotr(canvas->mask[i], 8 - rotation);
				canvas->mask[i] |= 0b00000001;
				canvas->mask[i] = rotr(canvas->mask[i], rotation);
				nextBitToRotate += bitsToNextLine;
			}
		}
	}
}