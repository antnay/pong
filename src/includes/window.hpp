#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_
#include "lib.hpp"
#include <iostream>

void initSDL(SDL_Window *&window, SDL_Renderer *&renderer);
void initWindow(SDL_Window *&window, int width, int height);
void initRender(SDL_Window *&window, SDL_Renderer *&renderer);
SDL_Surface *initSurface();
void cleanSDL(SDL_Window *window, SDL_Renderer *renderer);
Point<double> getCenter(int w, int h);

#endif
