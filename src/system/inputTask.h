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

#ifndef _SYSTEM_INPUTTASK_H_
#define _SYSTEM_INPUTTASK_H_

#include "system/kernel.h"
#include <SDL/SDL.h>

class CInputTask : public ITask
{
public:
    CInputTask();
    virtual ~CInputTask();

    bool start();
    void update();
    void stop();

    static unsigned char *keys;
    static CMMPointer< CMMDynamicBlob<unsigned char> > oldKeys;
    static int keyCount;

    static int dX, dY;
    static unsigned int buttons;
    static unsigned int oldButtons;

    static bool inline curKey(int index)
    {
        return (keys[index] != 0);
    }
    static bool inline oldKey(int index)
    {
        return ((*oldKeys)[index] != 0);
    }

    //some help functions to make certain things easier
    static bool inline keyDown(int index)
    {
        return (curKey(index)) && (!oldKey(index));
    }
    static bool inline keyStillDown(int index)
    {
        return (curKey(index)) && (oldKey(index));
    }
    static bool inline keyUp(int index)
    {
        return (!curKey(index)) && (oldKey(index));
    }
    static bool inline keyStillUp(int index)
    {
        return (!curKey(index)) && (!oldKey(index));
    }

    static bool inline curMouse(int button)
    {
        return (buttons&SDL_BUTTON(button)) != 0;
    }
    static bool inline oldMouse(int button)
    {
        return (oldButtons&SDL_BUTTON(button)) != 0;
    }

    static bool inline mouseDown(int button)
    {
        return (curMouse(button)) && (!oldMouse(button));
    }
    static bool inline mouseStillDown(int button)
    {
        return (curMouse(button)) && (oldMouse(button));
    }
    static bool inline mouseUp(int button)
    {
        return (!curMouse(button)) && (oldMouse(button));
    }
    static bool inline mouseStillUp(int button)
    {
        return (!curMouse(button)) && (!oldMouse(button));
    }

    AUTO_SIZE;
};

#endif      //_SYSTEM_INPUTTASK_H_
