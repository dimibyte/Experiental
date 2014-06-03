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

#ifndef _SYSTEM_SOUNDTASK_H_
#define _SYSTEM_SOUNDTASK_H_

#include "system/kernel.h"

namespace Experiental
{

class CSoundTask : public ITask
{
public:
    CSoundTask();
    virtual ~CSoundTask();

    bool start();
    void onSuspend();
    void update();
    void onResume();
    void stop();

    AUTO_SIZE;

protected:
    CMMPointer< CMMDynamicBlob<bool> > isPaused;
};

}

#endif      //_SYSTEM_SOUNDTASK_H_
