#include <math.h>
#include <stdbool.h>
#include <stdio.h>

// #define CLI_W 70
#define CLI_H 30
#define FONT_W 11//8
#define FONT_H 27//15

bool insideCircle(int x, int y, int a, int b, int R) {
    return (x - a) * (x - a) + (y - b) * (y - b) < R * R;
}

int main(void) {
    // double screenRatio = (double) FONT_H / FONT_W;
    // int CLI_W = CLI_H * screenRatio;
    // int rectH = CLI_H, rectW = rectH * screenRatio;
    
    // printf("screenRatio = %lf, rectW = %d\n", screenRatio, rectW);

    for (int i = 0; i < CLI_H; i++) {
        for (int j = 0; j < CLI_H; j++) {
            printf("%c", (insideCircle(i, j, CLI_H / 2, CLI_H / 2, CLI_H / 2)) ? '#' : ' ');
        }
        printf("\n");
    }

    return 0;
}

/*
уравнение окружности:
(y - a)^2 + (y - b)^2 = R^2
(a; b) -- центр окружности (обе равны радиусу)

диаметр равен высоте окна. x итерируется, y вычисляется из уравнения:
y = √(R^2 - (x - a)^2) + b
*/