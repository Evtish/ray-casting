#include <math.h>
#include <stdbool.h>
#include <stdio.h>

// #define CLI_W 70
#define CLI_H 30
#define FONT_W 11//8
#define FONT_H 27//15

bool insideCircle(int x, int y, int a, int b, int R) {
    // printf("%d\n", (x - a) * (x - a) + (y - b) * (y - b) < h * k);
    return (x - a) * (x - a) + (y - b) * (y - b) < R * R;
}

int main(void) {
    double screenRatio = (double) FONT_H / FONT_W;
    int cliW = CLI_H * screenRatio, h = CLI_H / 2, k = cliW / 2;
    // int rectH = CLI_H, rectW = rectH * screenRatio;
    
    // printf("screenRatio = %lf, h = %d, k = %d\n", screenRatio, h, k);

    for (int i = 0; i < CLI_H; i++) {
        for (int j = 0; j < cliW; j++) {
            // insideCircle(j, i, k, h, h, k);
            printf("%c", (insideCircle(j, i, k, h, h)) ? '#' : ' ');
        }
        printf("\n");
    }

    return 0;
}