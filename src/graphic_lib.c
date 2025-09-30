#include "graphic_lib.h"

#ifdef USE_SDL3
    SDL_Window *sdl_window = NULL;
    SDL_Renderer *sdl_renderer = NULL;
    SDL_Event sdl_event;
#endif

void graphics_init(void) {
    #ifdef USE_SDL3
        SDL_SetAppMetadata("Ray Casting", "0.2", "ru.evtish.ray-casting");

        if (!SDL_Init(SDL_INIT_VIDEO)) {
            SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
            exit(1);
        }

        if (!SDL_CreateWindowAndRenderer("Ray Casting", WINDOW_W, WINDOW_H, 0, &sdl_window, &sdl_renderer)) {
            SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
            exit(1);
        }
    #elif defined USE_NCURSES
        setlocale(LC_ALL, "");

        // if (initscr() == NULL) {
        //     printf("Couldn't initialize ncurses");
        //     exit(1);
        // }
        initscr();
        cbreak();
        noecho();
        curs_set(0);
        intrflush(stdscr, false);
        keypad(stdscr, true);

        if (has_colors()) {
            start_color();
            drawer_set_color_pairs();
        }
    #endif
}

void graphics_refresh(void) {
    #ifdef USE_SDL3
        SDL_RenderPresent(sdl_renderer);
        SDL_RenderClear(sdl_renderer);
    #elif defined USE_NCURSES
        refresh();
    #endif
}

void graphics_quit(void) {
    #ifdef USE_SDL3
        SDL_DestroyWindow(sdl_window);
        SDL_Quit();
    #elif defined USE_NCURSES
        endwin();
    #endif
}