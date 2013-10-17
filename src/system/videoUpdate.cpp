#include "system/videoUpdate.h"
#include <cassert>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include "system/CLog.h"

CMMPointer<Dator<int> > CVideoUpdate::screenWidth = 0;
CMMPointer<Dator<int> > CVideoUpdate::screenHeight = 0;
CMMPointer<Dator<int> > CVideoUpdate::screenBPP = 0;
int CVideoUpdate::scrWidth = 1280;
int CVideoUpdate::scrHeight = 720;
int CVideoUpdate::scrBPP = 32;

CVideoUpdate::CVideoUpdate()
{
}

CVideoUpdate::~CVideoUpdate()
{
}

bool CVideoUpdate::start()
{
//    assert(screenWidth && screenHeight && screenBPP);

    if(-1 == SDL_InitSubSystem(SDL_INIT_VIDEO))
    {
        CLog::get().write(LOG_CLIENT, IDS_GENERIC_SUB_INIT_FAIL, "Video", SDL_GetError());
        return false;
    }
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    int flags = SDL_OPENGL | SDL_ANYFORMAT | SDL_NOFRAME;

    if(!SDL_SetVideoMode(scrWidth, scrHeight, scrBPP, flags))
    {
        CLog::get().write(LOG_CLIENT, IDS_BAD_DISPLAYMODE, scrWidth, scrHeight, scrBPP, SDL_GetError());
        return false;
    }

    //hide the mouse cursor
    SDL_ShowCursor(SDL_DISABLE);

    return true;
}

void CVideoUpdate::update()
{
    SDL_GL_SwapBuffers();
}

void CVideoUpdate::stop()
{
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
