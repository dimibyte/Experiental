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

#include "system/soundTask.h"
//#include <fmodex/fmod.hpp>

CSoundTask::CSoundTask()
{
}

CSoundTask::~CSoundTask()
{
}

bool CSoundTask::start()
{
    //COpenALMixer::setSingleton(new COpenALMixer());
    /*if(false == FSOUND_Init(44100, 32, 0))
        return false;*/
    return true;
}

void CSoundTask::onSuspend()
{/*
    //pause all channels, storing the pause state in the isPaused array
    //once the states are stored we can use FSOUND_ALL to pause all
    //channels the easy way
    int chCount = FSOUND_GetMaxChannels();
    isPaused = new CMMDynamicBlob<bool>(chCount);
    for(int i = 0; i < chCount; i++)
    {
        if(FSOUND_IsPlaying(i))
        {
            isPaused->buffer[i] = true;
        }
        else
        {
            isPaused->buffer[i] = false;
        }
    }
    FSOUND_SetPaused(FSOUND_ALL, true);
*/}

void CSoundTask::update()
{
    //we don't need to do anything, FMOD does it all for us :)
}

void CSoundTask::onResume()
{/*
    //unpause all the flagged channels
    if(isPaused)
    {
        int chCount = FSOUND_GetMaxChannels();
        for(int i = 0; i < chCount; i++)
        {
            if(isPaused->buffer[i])
                FSOUND_SetPaused(i, false);
        }
        isPaused = 0;
    }
*/}

void CSoundTask::stop()
{/*
    FSOUND_Close();
*/}
