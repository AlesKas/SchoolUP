#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

struct point {
	unsigned char vertical : 1;
	unsigned char horizontal : 1;
};

 struct canvas2 {
	struct point** arr;
	int width;
	int height;
};

 struct canvas {
	 void* mask;
	 int width;
	 int height;
 };

struct canvas2* canvas2_create(int width, int height);
void canvas2_init(struct canvas2* canvas2);
void canvas2_free(struct canvas2* canvas2);
void canvas2_print(struct canvas2* canvas2);
void canvas2_hline(struct canvas2* canvas2, unsigned int x, unsigned int y, int length);
void canvas2_vline(struct canvas2* canvas2, unsigned int x, unsigned int y, int length);

int main() {
	struct canvas2* c = canvas2_create(20, 10);
	int size1 = sizeof(c->arr[0][0]);
	int size2 = sizeof(c->arr[0][1]);
	int size3 = sizeof(c->arr[0][2]);
	int size4 = sizeof(c->arr[0][3]);
	int size = size1 + size2 + size3 + size4;
	printf("%d\n", size);
	canvas2_hline(c, 3, 2, 13);
	canvas2_hline(c, 14, 5, -11);
	canvas2_vline(c, 4, 1, 6);
	canvas2_vline(c, 14, 6, -6);
	canvas2_vline(c, 9, 5, 20);
	canvas2_print(c);
	canvas2_free(c);
	return 0;
}

struct canvas2* canvas2_create(int width, int height)
{
	struct canvas2* temp = malloc(sizeof(struct canvas2));
	temp->height = height;
	temp->width = width;

	temp->arr = malloc(sizeof(struct point**) * height);
	for (int i = 0; i < height; i++)
		temp->arr[i] = malloc(sizeof(struct point*) * width);

	canvas2_init(temp);
	return temp;
}

void canvas2_init(struct canvas2* canvas2) {
	for (int i = 0; i < canvas2->height; i++)
		for (int j = 0; j < canvas2->width; j++)
		{
			canvas2->arr[i][j].horizontal = 0;
			canvas2->arr[i][j].vertical = 0;
		}	
}

void canvas2_free(struct canvas2* canvas2) {
	for (int i = 0; i < canvas2->height; i++)
		free(canvas2->arr[i]);
	free(canvas2->arr);
}

void canvas2_print(struct canvas2* canvas2) {
	for (int i = 0; i < canvas2->height; i++)
	{
		for (int j = 0; j < canvas2->width; j++)
		{
			if (canvas2->arr[i][j].horizontal == 0 && canvas2->arr[i][j].vertical == 0)
				printf(".");
			if (canvas2->arr[i][j].horizontal == 1 && canvas2->arr[i][j].vertical == 0)
				printf("-");
			if (canvas2->arr[i][j].horizontal == 0 && canvas2->arr[i][j].vertical == 1)
				printf("|");
			if (canvas2->arr[i][j].horizontal == 1 && canvas2->arr[i][j].vertical == 1)
				printf("+");
		}
		printf("\n");
	}
}

void canvas2_hline(struct canvas2* canvas2, unsigned int x, unsigned int y, int length) {
	int i = 0;
	if (length > 0) {
		for (int i = x; i < x + length; i++) {
			if (i == canvas2->width || i < 0) {
				return;
			}
			canvas2->arr[y][i].horizontal = 1;
		}
	}
	else {
		int linesDrawn = 0;
		int i = x;
		while (linesDrawn < abs(length)) {
			if (i == -1 || i == canvas2->width) {
				return;
			}
			canvas2->arr[y][i].horizontal = 1;
			i--;
			linesDrawn++;
		}
	}
}

void canvas2_vline(struct canvas2* canvas2, unsigned int x, unsigned int y, int length) {
	int i;
	if (length > 0) {
		for (int i = y; i < y + length; i++) {
			if (i == canvas2->height || i < 0) {
				return;
			}
			canvas2->arr[i][x].vertical = 1;
		}
	}
	else {
		int linesDrawn = 0;
		int i = y;
		while (linesDrawn < abs(length)) {
			if (i == -1 || i == canvas2->height) {
				return;
			}
			canvas2->arr[i][x].vertical = 1;
			i--;
			linesDrawn++;
		}
	}

}