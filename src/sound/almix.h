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

#ifndef _SOUND_ALMIX_H_
#define _SOUND_ALMIX_H_

#include <SDL/SDL_mixer.h>
#include <AL/al.h>
#include <AL/alc.h>

#include <string>

#include "system/singleton.h"

class COpenALMixer : public Singleton<COpenALMixer>
{
private:
    ALuint buffer;
    ALuint source;
    ALCdevice* device;
    ALCcontext* context;
public:
    COpenALMixer();
    virtual ~COpenALMixer();

    void playSound(std::string wavfile, bool loop);    //maybe bool instead of void?
//    void playSound(std::string flacfile);
};

#endif      //_SOUND_ALMIX_H_
