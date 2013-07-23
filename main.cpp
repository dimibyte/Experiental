#include "main.h"
#include "globals.h"
#include "system/SDL.h"
#include "graphics/openGL.h"

int main(int argc, char** argv)
{
    if(!initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP))
        return 1;
    if(!initGL(SCREEN_WIDTH, SCREEN_HEIGHT))
        return 2;
    /***    Loop    ***/
    while(!bQuit)
    {
        /***    Events     ***/
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                bQuit = true;
            /// Keyboard ///
            if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_ESCAPE)
                    bQuit = true;
            }
            /// Mouse ///
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if(event.button.button == SDL_BUTTON_MIDDLE)
                    bQuit = true;
            }
        }
        /***    Logic    ***/

        /***    Render    ***/

        /***    Debug    ***/

        /// Screen update
        SDL_GL_SwapBuffers();
        SDL_Delay(1000/SCREEN_FPSL);
    }
    /***    Exiting    ***/
    cleanupSDL();
    return 0;
}
