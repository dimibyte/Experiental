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

#include "sound/almix.h"
#include <iostream>

COpenALMixer::COpenALMixer()
{
    ALuint buffer;
    ALuint source;

    //initiate OpenAL
    ALCdevice* device;
    device = alcOpenDevice(NULL);

    ALCcontext* context;
    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);
    alGenBuffers(1, &buffer);
    alGenSources(1, &source);

    //initiate SDL_Mixer
    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = 2;
    int audio_buffers = 4096;

    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0)
    {
        //log an error
        exit(1);
    }
}

COpenALMixer::~COpenALMixer()
{
    Mix_CloseAudio();

    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);

    alcDestroyContext(context);
    alcCloseDevice(device);
}

void COpenALMixer::playSound(std::string wavfile, bool loop = false)
{
    //load wave file
    Mix_Chunk *sound = Mix_LoadWAV("some.wav");

    if(sound == NULL)
    {
        //log smt like "Unable to load WAV file: ..." with Mix_GetError()
        std::cout<<"Unable to load WAV file: "<<Mix_GetError()<<std::endl;
    }

    //transfer Mix_Chunk data and length to OpenAL buffer
    alBufferData(buffer, AL_FORMAT_STEREO16, sound->abuf, sound->alen, 44100);

    //generate new sound
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    alSourcef(source, AL_PITCH, 1.0f);
    alSourcef(source, AL_GAIN, 1.0f);

    if(loop)
        alSourcei(source, AL_LOOPING, AL_TRUE);
    else
        alSourcei(source, AL_LOOPING, AL_FALSE);

    //play sound
    alSourcePlay(source);
}


/*/

typedef struct {
int allocated;
Uint8 *abuf;
Uint32 alen;
Uint8 volume;
} Mix_Chunk;

So now you know you have access to all this data.

/*/

/*/

Just a little note:
If you want to make 3D sound working in openal, you have to use MONO sound, so the following lines will be differend:

// before
int audio_channels = 2;
...
alBufferData(buffer, AL_FORMAT_STEREO16, sound->abuf, sound->alen, 44100);

// after
int audio_channels = 1;
...
alBufferData(buffer, AL_FORMAT_MONO16, sound->abuf, sound->alen, 44100);

/*/
