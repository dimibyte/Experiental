#ifndef _SYSTEM_SDL_H_
#define _SYSTEM_SDL_H_

#ifdef _WIN32
#pragma comment (lib, "SDLmain.lib")
#pragma comment (lib, "SDL.lib")
#pragma comment (lib, "SDL_image.lib")
#pragma comment (lib, "SDL_ttf.lib")
#endif      // _WIN32

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "globals.h"

SDL_Surface & initSDL(int screenWidth, int screenHeight, int screenBPP);
void cleanupSDL();
SDL_Surface& returnScreen();

#endif      //_SDL_INIT_H_
