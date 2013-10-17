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

///Runtime Profiler

#include <SDL/SDL.h>
#include <cassert>
#include "system/profiler.h"
#include "system/CLog.h"

int CProfileSample::lastOpenedSample = -1;
int CProfileSample::openSampleCount = 0;
CProfileSample::profileSample CProfileSample::samples[MAX_PROFILER_SAMPLES];
IProfilerOutputHandler *CProfileSample::outputHandler = 0;
float CProfileSample::rootBegin = 0.0f;
float CProfileSample::rootEnd = 0.0f;
bool CProfileSample::bProfilerIsRunning = true;

void CProfileLogHandler::beginOutput()
{
    CLog::get().write(LOG_APP, IDS_PROFILE_HEADER1);
    CLog::get().write(LOG_APP, IDS_PROFILE_HEADER2);
}

void CProfileLogHandler::endOutput()
{
    CLog::get().write(LOG_APP, "\n");
}

void CProfileLogHandler::sample(float fMin, float fAvg, float fMax, int callCount, std::string name, int parentCount)
{
    char namebuf[256], indentedName[256];
    char avg[16], min[16], max[16], num[16];

    sprintf(avg, "%3.1f", fAvg);
    sprintf(min, "%3.1f", fMin);
    sprintf(max, "%3.1f", fMax);
    sprintf(num, "%3d", callCount);

    strcpy(indentedName, name.c_str());
    for(int indent = 0; indent < parentCount; ++indent)
    {
        sprintf(namebuf, " %s", indentedName);
        strcpy(indentedName, namebuf);
    }

    CLog::get().write(LOG_APP, IDS_PROFILE_SAMPLE, min, avg, max, num, indentedName);
}

inline float CProfileSample::getTime()
{
    return ((float)SDL_GetTicks())/1000.0f;
}

CProfileSample::CProfileSample(std::string samplename)
{
    if(!bProfilerIsRunning)
        return;
    //The first thing we need to do is restore our previuous pieces of sample
    //data from storage. That is, look in the samples[] array to see if there's
    //a valid sample with our name on it
    int i = 0;
    //If we don't find it, we're going to need to create a new sample, and rather
    //than looping through the list a second time we store the first non-valid
    //index that we find this time round
    int storeIndex = -1;
    for(i = 0; i < MAX_PROFILER_SAMPLES; ++i)
    {
        if(!samples[i].bIsValid)
        {
            if(storeIndex < 0)
                storeIndex = i;
        }
        else
        {
            if(samples[i].name == samplename)
            {
                //this is the sample we want
                //check that it's not already open
                //assert only works in debug builds, but given that you don't use
                //the profiler in release builds, it doesn't really matter
                assert(!samples[i].bIsOpen && "Tried to profile a sample which was already being profiled");
                //first, store its index
                iSampleIndex = i;
                //the parent sample is the last opened sample
                iParentIndex = lastOpenedSample;
                lastOpenedSample = i;
                //and the number of parents is the number of open samples (excluding ourselves)
                samples[i].parentCount = openSampleCount;
                ++openSampleCount;
                samples[i].bIsOpen = true;
                //increment the number of times we've been called
                ++samples[i].callCount;
                //finally (more or less) store the curent time to start the sample
                samples[i].startTime = getTime();
                //if this has no parent, it must be the 'main loop' sample, so copy to the global timer as well
                if(iParentIndex < 0)
                    rootBegin = samples[i].startTime;
                //done
                return;
            }
        }
    }
    //we've not found it, so it must be a new sample
    //use the storeIndex value to store the new sample
    assert(storeIndex >= 0 && "Profiler has run out of sample slots!");
    samples[storeIndex].bIsValid = true;
    samples[storeIndex].name = samplename;
    iSampleIndex = storeIndex;
    iParentIndex = lastOpenedSample;
    lastOpenedSample = storeIndex;
    samples[storeIndex].parentCount = openSampleCount;
    openSampleCount++;
    samples[storeIndex].bIsOpen = true;
    samples[storeIndex].callCount = 1;

    //init the statistics for this sample
    samples[storeIndex].totalTime = 0.0f;
    samples[storeIndex].childTime = 0.0f;
    samples[storeIndex].startTime = getTime();
    if(iParentIndex < 0)
        rootBegin = samples[storeIndex].startTime;
}

CProfileSample::~CProfileSample()
{
    if(!bProfilerIsRunning)
        return;
    float fEndTime = getTime();
    //phew... ok, we're done timing
    samples[iSampleIndex].bIsOpen = false;
    //calculate the time taken this profile, for ease of use later on
    float fTimeTaken = fEndTime - samples[iSampleIndex].startTime;

    if(iParentIndex >= 0)
    {
        samples[iParentIndex].childTime += fTimeTaken;
    }
    else
    {
        //no parent, so this is the end of the main loop sample
        rootEnd = fEndTime;
    }
    samples[iSampleIndex].totalTime += fTimeTaken;
    lastOpenedSample = iParentIndex;
    --openSampleCount;
};

void CProfileSample::output()
{
    if(!bProfilerIsRunning)
        return;

    assert(outputHandler && "Profiler has no output handler set");

    outputHandler->beginOutput();

    for(int i = 0; i < MAX_PROFILER_SAMPLES; ++i)
    {
        if(samples[i].bIsValid)
        {
            float sampleTime, percentage;
            //calculate the time spend on the sample itself (excluding children)
            sampleTime = samples[i].totalTime - samples[i].childTime;
            percentage = (sampleTime / (rootEnd - rootBegin)) * 100.0f;

            //add it to the sample's values
            float totalPc;
            totalPc = samples[i].averagePc * samples[i].dataCount;
            totalPc += percentage;
            samples[i].dataCount++;
            samples[i].averagePc = totalPc / samples[i].dataCount;
            if((samples[i].minPc == -1) || (percentage < samples[i].minPc))
                samples[i].minPc = percentage;
            if((samples[i].maxPc == -1) || (percentage > samples[i].maxPc))
                samples[i].maxPc = percentage;

            //output these values
            outputHandler->sample(samples[i].minPc,
                                  samples[i].averagePc,
                                  samples[i].maxPc,
                                  samples[i].callCount,
                                  samples[i].name,
                                  samples[i].parentCount);

            //reset the sample for next time
            samples[i].callCount = 0;
            samples[i].totalTime = 0;
            samples[i].childTime = 0;
        }
    }

    outputHandler->endOutput();
}

void CProfileSample::resetSample(std::string sampleName)
{
    for(int i = 0; i < MAX_PROFILER_SAMPLES; ++i)
    {
        if((samples[i].bIsValid) && (samples[i].name == sampleName))
        {
            //found it
            //reset avg/min/max ONLY
            //because the sample may be running
            samples[i].maxPc = samples[i].minPc = -1;
            samples[i].dataCount = 0;
            return;
        }
    }
}

void CProfileSample::resetAll()
{
    for(int i = 0; i < MAX_PROFILER_SAMPLES; ++i)
    {
        if(samples[i].bIsValid)
        {
            samples[i].maxPc = samples[i].minPc = -1;
            samples[i].dataCount = 0;
        }
    }
}



