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

#ifndef _PROFILER_H_
#define _PROFILER_H_

#include <string>

#define MAX_PROFILER_SAMPLES 50


class IProfilerOutputHandler
{
public:
    virtual void beginOutput() = 0;
    virtual void sample(float fMin, float fAvg, float fMax, int callCount, std::string name, int parentCount) = 0;
    virtual void endOutput() = 0;
};

class CProfileLogHandler : public IProfilerOutputHandler
{
public:
    void beginOutput();
    void endOutput();
    void sample(float fMin, float fAvg, float fMax, int callCount, std::string name, int parentCount);
};

class CProfileSample
{
public:
    CProfileSample(std::string sampleName);
    ~CProfileSample();

    static void output();

    static void resetSample(std::string sampleName);
    static void resetAll();

    static IProfilerOutputHandler *outputHandler;

protected:
    //index into the array of samples
    int iSampleIndex;
    int iParentIndex;

    inline float getTime();

    struct profileSample
    {
        profileSample()
        {
            bIsValid = false;
            dataCount = 0;
            averagePc = minPc = maxPc = -1;
        }

        bool bIsValid;      //whether or not this sample is valid to be used
        bool bIsOpen;       //is this sample currently being profiled?
        unsigned int callCount;     //number of times this sample has been executed
        std::string name;   //name of the sample

        float startTime;    //starting time on the clock, in seconds
        float totalTime;    //total time recorded across all executions of this sample
        float childTime;    //total time taken by children of this sample

        int parentCount;    //number of parents this sample has
                        // (useful for neat indenting)

        float averagePc;    //average percentage of game loop time taken up
        float minPc;        //minimum percentage of game loop time taken up
        float maxPc;        //maximum percentage of game loop time taken up
        unsigned long dataCount;    //number of times values have been stored since sample creation/reset

    };
    static profileSample samples[MAX_PROFILER_SAMPLES];

    static int lastOpenedSample;
    static int openSampleCount;
    static float rootBegin, rootEnd;
};

#endif      //_PROFILER_H_