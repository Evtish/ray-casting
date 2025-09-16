#include <stdbool.h>
#include <stdio.h>

#include "calc.h"
#include "vec2.h"
#include "dda.h"

#define CLI_W 24
#define CLI_H 24
#define FONT_W 11//8
#define FONT_H 27//15

int main(void) {
    int worldMap[CLI_H][CLI_W] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    char textures[] = {' ', ',', ':', 'o', '#', '@'};

    vec2 playerPos = {12.0, 12.0};
    vec2 playerDir = {0.0, 1.0};
    vec2 cameraPlane = {0.66, 0};

    // while (true) {
        for (int i = 0; i <= CLI_W; i++) {
            double screenPosX = fmap(i, 0, CLI_W, -1.0, 1.0);
            vec2 rayDir = vec2_add(playerDir, vec2_scalarMult_n(cameraPlane, screenPosX));

            d_vec2 playerMapBox = (d_vec2) {playerPos.x, playerPos.y};
            d_vec2 stepDir = vec2_normalize(rayDir);

            vec2 deltaDist = {
                (rayDir.x == 0) ? 1e14 : fabs(1 / rayDir.x),
                (rayDir.y == 0) ? 1e14 : (1 / rayDir.y)
            };
            vec2 sideDist = {
                getSideDistCoord(rayDir.x, playerPos.x, playerMapBox.x, deltaDist.x),
                getSideDistCoord(rayDir.y, playerPos.y, playerMapBox.y, deltaDist.y)
            };

            double perpWallDist;

            int hit = 0;
            int side;

            // if (rayDir.x < 0) sideDist.x = (playerPos.x - playerMapBox.x) * deltaDist.x;
            // else sideDist.x = (playerMapBox.x + 1.0 - playerPos.x) * deltaDist.x;
            // if (rayDir.y < 0) sideDist.y = (playerPos.y - playerMapBox.y) * deltaDist.y;
            // else sideDist.y = (playerMapBox.y + 1.0 - playerPos.y) * deltaDist.y;

            // printf("sideDist.x = %lf, sideDist.y = %lf\n", sideDist.x, sideDist.y);

            // DDA
            while (hit == 0)
            {
                // jump to the nearest map square
                if (sideDist.x < sideDist.y) {
                    sideDist.x += deltaDist.x;
                    playerMapBox.x += stepDir.x;
                    side = 0;
                }
                else {
                    sideDist.y += deltaDist.y;
                    playerMapBox.y += stepDir.y;
                    side = 1;
                }
                if (worldMap[playerMapBox.x][playerMapBox.y] > 0) hit = 1;
            } 
        }
    // }
    
    return 0;
}
