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

#include "system/SDL.h"

namespace Experiental
{

/*SDL_Window *screen = NULL;

SDL_Surface& initSDL(int screenWidth, int screenHeight)
{*/
    /*if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTTHREAD | SDL_INIT_TIMER) < 0)
        return false;*/
 /*   SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);*/
    /*if((SDL_Surface* screen = SDL_SetVideoMode((const int)screenWidth, (const int)screenHeight, (const int)screenBPP, SDL_OPENGL)) == NULL)
        return false;*/
 /*   if(screen != NULL){
		SDL_DestroyWindow(screen);
		screen = NULL;
	}

    screen = SDL_CreateWindow("Experiental ver. ",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    (const int)screenWidth,
                                    (const int)screenHeight,
                                    SDL_WINDOW_OPENGL);
    SDL_ShowCursor(SDL_DISABLE) ;
    SDL_EnableUNICODE(1) ;
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL) ;

    return *screen;
}
*/
void cleanupSDL()
{
    SDL_Quit();
}

}
