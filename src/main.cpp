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

#include "main.h"
#include "globals.h"
#include "system/SDL.h"
#include "graphics/openGL.h"
#include "game.h"
#include "sound/almix.h"

#include <iostream>

int main(int argc, char** argv)
{
    //Game::Start();

    new CApplication();
    CApplication::getSingleton().run(argc, argv);
    delete CApplication::getSingletonPtr();

    //clean up any remaining unreleased objects
    IMMObject::collectRemainingObjects(true);

    return 0;
}
