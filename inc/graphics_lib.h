#pragma once

#include <stdlib.h>
#ifdef USE_SDL3
    #include <SDL3/SDL.h>
    #include <SDL3/SDL_main.h>

    #define WINDOW_W 1920
    #define WINDOW_H 1080

    extern SDL_Window *sdl_window;
    extern SDL_Renderer *sdl_renderer;
#elif defined USE_NCURSES
    #include <locale.h>
    #include <ncurses.h>
    #include "drawer.h"

    #define WINDOW_W getmaxx(stdscr)
    #define WINDOW_H getmaxy(stdscr)
#endif

void graphics_init(void);
void graphics_refresh(void);
void graphics_quit(void);
