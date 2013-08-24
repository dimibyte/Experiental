#include "system/globalTimer.h"
#include <SDL/SDL.h>

float CGlobalTimer::dT = 0.0f;
unsigned long CGlobalTimer::thisFrameIndex = 0;
unsigned long CGlobalTimer::lastFrameIndex = 0;

bool CGlobalTimer::start()
{
    thisFrameIndex = SDL_GetTicks();
    lastFrameIndex = thisFrameIndex;
    dT = 0.0f;
    return true;
}

void CGlobalTimer::update()
{
    lastFrameIndex = thisFrameIndex;
    thisFrameIndex = SDL_GetTicks();
    dT = ((float)(thisFrameIndex - lastFrameIndex))/1000.0f;
}

void CGlobalTimer::stop()
{

}
