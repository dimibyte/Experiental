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
#include "app.h"

#include <iostream>
#include <cstdio>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif
float s = 0;
void print_SDL_version(char* preamble, SDL_version* v) {
   printf("%s %u.%u.%u\n", preamble, v->major, v->minor, v->patch);
}

void print_SDL_versions() {
    SDL_version ver;

    // Prints the compile time version
    SDL_VERSION(&ver);
    print_SDL_version((char*)"SDL compile-time version", &ver);

    // Prints the run-time version
    SDL_GetVersion(&ver);
    print_SDL_version((char*)"SDL runtime version", &ver);
}

int main(int argc, char** argv)
{
    //Game::Start();
    print_SDL_versions();

    CApplication::setSingleton(new CApplication());
    CApplication::getSingleton().run(argc, argv);
    delete CApplication::getSingletonPtr();

    //clean up any remaining unreleased objects
    IMMObject::collectRemainingObjects(true);

    return 0;
}
