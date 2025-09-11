#include <stdio.h>

#define CLI_W 120
#define CLI_H 40
#define FONT_W 8
#define FONT_H 15

int main(void) {
    double screenRatio = (double) CLI_W * FONT_W / CLI_H / FONT_H;
    int rectH = CLI_H, rectW = rectH * screenRatio;
    
    // printf("screenRatio = %lf, rectW = %d\n", screenRatio, rectW);

    for (int i = 0; i < rectH; i++) {
        for (int j = 0; j < rectW; j++)
            printf("%c", '#');
        printf("\n");
    }

    return 0;
}

/*
уравнение окружности:
(x - a)^2 + (y - b)^2 = R^2
(a; b) -- центр окружности (обе равны радиусу)

диаметр равен высоте окна. x итерируется, y вычисляется из уравнения:
y = √(R^2 - (x - a)^2) + b
*/