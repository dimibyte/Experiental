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
    _gameState = Game::playing;

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
    if(_gameState == Game::exiting)
        return true;
    else
        return false;
}

void Game::GameLoop()
{
    SDL_Event event;
    double last_time_pulse = 0.001 * static_cast<double>(SDL_GetTicks());   //for CEGUI
    bool must_quit = false;     //for CEGUI

    switch(Game::_gameState)
    {
        case Game::showingMenu:
        {
        }

        case Game::playing:
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
