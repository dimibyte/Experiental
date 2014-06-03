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

#ifndef _SYSTEM_INTERPOLATORS_H_
#define _SYSTEM_INTERPOLATORS_H_

#include "system/kernel.h"

namespace Experiental
{

class CInterpolatorUpdater : public ITask
{
public:
    bool start();
    void update();
    void stop();
    AUTO_SIZE;
};

class IInterpolator : public IMMObject
{
protected:
    float &target;
    static std::list<CMMPointer<IInterpolator> > interpolators;
public:
    IInterpolator(float &t);
    virtual ~IInterpolator();

    bool bFreeze;

    virtual void update(float dt) = 0;
    void kill();

    friend class CInterpolatorUpdater;
    AUTO_SIZE;
};

class ITimebasedInterpolator : public IInterpolator
{
protected:
    float elapsedTime, totalTime;
    virtual void calculate() = 0;
public:
    void reset();
    void update(float dt);
    ITimebasedInterpolator(float &targ, float time);
    AUTO_SIZE;
};

class CLinearTimeInterpolator : public ITimebasedInterpolator
{
protected:
    float startVal, endVal;
    void calculate();
public:
    CLinearTimeInterpolator(float &targ, float time, float sV, float eV);
    AUTO_SIZE;
};

class CQuadraticTimeInterpolator : public ITimebasedInterpolator
{
protected:
    float startVal, midVal, endVal;
    void calculate();
public:
    CQuadraticTimeInterpolator(float &targ, float time, float sV, float mV, float eV);
    AUTO_SIZE;
};

class CCubicTimeInterpolator : public ITimebasedInterpolator
{
protected:
    float startVal, midVal1, midVal2, endVal;
    void calculate();
public:
    CCubicTimeInterpolator(float &targ, float time, float sV, float mV1, float mV2, float eV);
    AUTO_SIZE;
};

}

#endif // _SYSTEM_INTERPOLATORS_H_

