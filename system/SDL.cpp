#include "system/SDL.h"

bool initSDL(int screenWidth, int screenHeight, int screenBPP)
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTTHREAD | SDL_INIT_TIMER) < 0)
        return false;
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    if(SDL_SetVideoMode((const int)screenWidth, (const int)screenHeight, (const int)screenBPP, SDL_OPENGL) == NULL)
        return false;
    //SDL_WM_SetCaption("", NULL);

    return true;
}

void cleanupSDL()
{
    SDL_Quit();
}
