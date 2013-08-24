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

#include "system/inputTask.h"

unsigned char *CInputTask::keys = 0;
CMMPointer<CMMDynamicBlob<unsigned char> > CInputTask::oldKeys = 0;
int CInputTask::keyCount = 0;
int CInputTask::dX = 0;
int CInputTask::dY = 0;
unsigned int CInputTask::buttons = 0;
unsigned int CInputTask::oldButtons = 0;

CInputTask::CInputTask()
{
}

CInputTask::~CInputTask()
{
}

bool CInputTask::start()
{
    keys = SDL_GetKeyState(&keyCount);
    oldKeys = new CMMDynamicBlob<unsigned char>(keyCount);
    dX = dY = 0;
    SDL_PumpEvents(); SDL_PumpEvents();
    return true;
}

void CInputTask::update()
{
    SDL_PumpEvents();

    oldButtons = buttons;
    buttons = SDL_GetRelativeMouseState(&dX, &dY);

    memcpy((unsigned char*)(*oldKey), keys, sizeof(unsigned char) *keyCount);
    keys = SDL_GetKeyState(&keyCount);
}

void CInputTask::stop()
{
    keys = 0;
    oldKeys = 0;
}


