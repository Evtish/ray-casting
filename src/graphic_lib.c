#include "graphic_lib.h"

#ifdef USE_SDL3
    SDL_Window *sdl_window = NULL;
    SDL_Renderer *sdl_renderer = NULL;
    SDL_Event sdl_event;

    void graphics_init(void) {
        SDL_SetAppMetadata("Ray Casting", "0.2", "Ray Casting");

        if (!SDL_Init(SDL_INIT_VIDEO)) {
            SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
            exit(1);
        }

        if (!SDL_CreateWindowAndRenderer("Ray Casting", WINDOW_W, WINDOW_H, SDL_WINDOW_FULLSCREEN, &sdl_window, &sdl_renderer)) {
            SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
            exit(1);
        }
    }

    void graphics_refresh(void) {
        SDL_RenderPresent(sdl_renderer);
        SDL_RenderClear(sdl_renderer);
    }

    void graphics_quit(void) {
        SDL_DestroyWindow(sdl_window);
        SDL_Quit();
    }

#elif defined USE_NCURSES
    void graphics_init(void) {
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
    }

    void graphics_refresh(void) {
        refresh();
    }

    void graphics_quit(void) {
        endwin();
    }
#endif
