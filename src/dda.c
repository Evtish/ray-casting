#include "dda.h"

double getSideDistCoord(
    const double rayDirCoord,
    const double playerPosCoord,
    const int playerMapBoxCoord,
    const double deltaDistCoord
) {
    if (rayDirCoord < 0)
        return (playerPosCoord - playerMapBoxCoord) * deltaDistCoord;
    else
        return (playerMapBoxCoord + 1.0 - playerPosCoord) * deltaDistCoord;
}