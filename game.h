#ifndef _GAME_H_
#define _GAME_H_

class Game
{
public:
    static void Start();

private:
    static bool isExiting();
    static void GameLoop();
    enum GameState {uninitialized, showingSplash, paused, showingMenu, playing, exiting};
    static GameState _gameState;
    //static SDL_Surface *screen;
};

#endif      //_GAME_H_
