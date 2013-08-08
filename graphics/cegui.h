#ifndef _CEGUI_H_
#define _CEGUI_H_

#include <CEGUI/CEGUI.h>
#include <SDL/SDL.h>

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
