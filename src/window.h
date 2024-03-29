#ifndef _WINDOW_H_
#define _WINDOW_H_
#include "/opt/homebrew/opt/sdl2/include/SDL2/SDL.h"

void initSDL(SDL_Window *&window, SDL_Surface *surface);
void initWindow(SDL_Window *&window, int width, int height);
SDL_Surface *initSurface();
void cleanSDL(SDL_Window *window);

#endif
