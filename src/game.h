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

#ifndef _GAME_H_
#define _GAME_H_

#include "engine.h"

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

class CApplication : public Singleton<CApplication>
{
public:
    CMMPointer<CVideoUpdate> videoTask;
    CMMPointer<CGlobalTimer> globalTimer;
    CMMPointer<CInputTask> inputTask;
    CMMPointer<CSoundTask> soundTask;
    CMMPointer<COurTestTask> tt;
    CMMPointer<CLogoTask> lt;

    void run(int argc, char** argv);
};

#endif      //_GAME_H_
