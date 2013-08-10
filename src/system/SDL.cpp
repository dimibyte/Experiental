#include "system/SDL.h"

SDL_Surface& initSDL(int screenWidth, int screenHeight, int screenBPP)
{
    /*if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTTHREAD | SDL_INIT_TIMER) < 0)
        return false;*/
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTTHREAD | SDL_INIT_TIMER);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    /*if((SDL_Surface* screen = SDL_SetVideoMode((const int)screenWidth, (const int)screenHeight, (const int)screenBPP, SDL_OPENGL)) == NULL)
        return false;*/
    SDL_Surface* screen = SDL_SetVideoMode((const int)screenWidth, (const int)screenHeight, (const int)screenBPP, SDL_OPENGL);
    //SDL_WM_SetCaption("", NULL);
    SDL_ShowCursor(SDL_DISABLE) ;
    SDL_EnableUNICODE(1) ;
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL) ;

    return *screen;
}

void cleanupSDL()
{
    SDL_Quit();
}
