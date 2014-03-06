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

#include "system/interpolators.h"
#include "system/globalTimer.h"
#include "system/profiler.h"
#include "misc.h"       //clamp
#include <algorithm>    //std::find

std::list< CMMPointer<IInterpolator> > IInterpolator::interpolators;

IInterpolator::IInterpolator(float &t) : target(t)
{
    interpolators.push_back(this);
    bFreeze = false;
}

IInterpolator::~IInterpolator()
{
}

void IInterpolator::kill()
{
    CMMPointer<IInterpolator> t = this;
    std::list<CMMPointer<IInterpolator> >::iterator it = (std::find(interpolators.begin(), interpolators.end(), t));
    if(it != interpolators.end())
        (*it) = 0;
}

bool CInterpolatorUpdater::start() { return true; }
void CInterpolatorUpdater::stop() { IInterpolator::interpolators.clear(); }
void CInterpolatorUpdater::update()
{
    PROFILE("Interpolator task");
    std::list<CMMPointer<IInterpolator> >::iterator it, ite = IInterpolator::interpolators.end(), itT;
    for(it = IInterpolator::interpolators.begin(); it != ite; it++)
    {
        if((*it).isValid())
        {
            (*it)->update(CGlobalTimer::dT);
        }
        else
        {
            //remove invalid entries from the list, just to keep things fast
            itT = it;
            --it;
            IInterpolator::interpolators.erase(itT);
        }
    }
}

void CLinearTimeInterpolator::calculate()
{
    //calculate b, keeping it clamped to the range [0, 1]
    float b = clamp(elapsedTime / totalTime, 0, 1);
    target = startVal * (1 - b) + endVal * b;
}

void CQuadraticTimeInterpolator::calculate()
{
    float b = clamp(elapsedTime / totalTime, 0, 1), a = 1 - b;
    target = startVal * a * a + midVal * 2 * a * b  + endVal * b * b;
}

void CCubicTimeInterpolator::calculate()
{
    float b = clamp(elapsedTime / totalTime, 0, 1), a = 1 - b;
    target = startVal * a*a*a + midVal1 * 3 * a*a * b + midVal2 * 3 * a * b*b + endVal * b*b*b;
}

void ITimebasedInterpolator::update(float dt)
{
    if(bFreeze)
        return;
    elapsedTime += dt;
    calculate();
    if(elapsedTime > totalTime)
        kill();
}
