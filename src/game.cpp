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

#include "game.h"
#include "globals.h"
#include "system/SDL.h"
#include "graphics/openGL.h"
#include "graphics/cegui.h"



void Game::Start()
{
    if(_gameState != uninitialized)
        return;

    SDL_Surface & screen = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP);
    if(!initGL(SCREEN_WIDTH, SCREEN_HEIGHT))
        return;
    CEGUI::WindowManager& winManager = GUI::init_CEGUI(screen) ;
    //CEGUI::OpenGLRenderer& myRenderer = CEGUI::OpenGLRenderer::create();
    GUI::create_gui( winManager ) ;
    _gameState = playing;

    /***    Loop    ***/
    while (!isExiting())
    {
        GameLoop();
    }

    /***    Exiting    ***/
    cleanupSDL();
}

bool Game::isExiting()
{
    if(_gameState == exiting)
        return true;
    else
        return false;
}

void Game::GameLoop()
{
    SDL_Event event;
    double last_time_pulse = 0.001 * static_cast<double>(SDL_GetTicks());   //for CEGUI
    bool must_quit = false;     //for CEGUI

    switch(_gameState)
    {
        case showingMenu: { }

        case playing:
        {
            /***    Events     ***/
            while(SDL_PollEvent(&event))
            {
                //CEGUI
                GUI::inject_time_pulse(last_time_pulse);
                GUI::inject_input(must_quit);

                if(event.type == SDL_QUIT)
                    _gameState = exiting;
                /// Keyboard ///
                if(event.type == SDL_KEYDOWN)
                {
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                        _gameState = exiting;
                }
                /// Mouse ///
                if(event.type == SDL_MOUSEBUTTONDOWN)
                {
                    if(event.button.button == SDL_BUTTON_MIDDLE)
                        _gameState = exiting;
                }

                if(must_quit) { _gameState = exiting; }
            }
            /***    Logic    ***/

            /***    Render    ***/
            glClear( GL_COLOR_BUFFER_BIT ) ;
            GUI::render_gui();

            /***    Debug    ***/

            /// Screen update
            SDL_GL_SwapBuffers();
            SDL_Delay(1000/SCREEN_FPSL);
            break;
        }
        default:
            break;
    }
}

Game::GameState Game::_gameState = uninitialized;
