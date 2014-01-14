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

#ifndef _CEGUI_H_
#define _CEGUI_H_

#ifdef _WIN64
#ifndef POINTER_64
#define POINTER_64 __ptr64
#endif
#endif  //_WIN64

#include <CEGUI/CEGUI.h>
#include "system/SDL.h"

class GUI
{
public:
    static void handle_mouse_down(Uint8 button);
    static void handle_mouse_up(Uint8 button);
    static void inject_input(bool &must_quit);
    static void inject_time_pulse(double &last_time_pulse);
    static void render_gui();
    static void set_CEGUI_paths();
    static CEGUI::WindowManager & init_CEGUI( SDL_Surface & surface );
    static void create_gui( CEGUI::WindowManager & winManager );
};


#endif      //_CEGUI_H_
