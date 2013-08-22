/*
 *  This file is part of Experiental.
 *
 *  Experiental is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  Experiental is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Experiental.  If not, see <http://www.gnu.org/licenses/>.
 */

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
#include <SDL/SDL_net.h>

#include "globals.h"

SDL_Surface & initSDL(int screenWidth, int screenHeight, int screenBPP);
void cleanupSDL();
SDL_Surface& returnScreen();

#endif      //_SYSTEM_SDL_H_
