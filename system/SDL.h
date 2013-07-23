#ifndef _SYSTEM_SDL_H_
#define _SYSTEM_SDL_H_

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "globals.h"

bool initSDL(int screenWidth, int screenHeight, int screenBPP);
void cleanupSDL();

#endif      //_SDL_INIT_H_
