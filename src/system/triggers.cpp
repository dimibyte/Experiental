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

#include "system/triggers.h"
#include "system/profiler.h"
#include <algorithm>

namespace Experiental
{

std::list< CMMPointer<ITrigger> > ITrigger::triggerList;

ITrigger::ITrigger(Functor *h, bool fo)
{
    handler = h;
    bFireOnce = fo;
    triggerList.push_back(this);
}

ITrigger::~ITrigger()
{
}

void ITrigger::kill()
{
    CMMPointer<ITrigger> t = this;
    std::list< CMMPointer<ITrigger> >::iterator it =
        (std::find(triggerList.begin(), triggerList.end(), t));
    if(it != triggerList.end())
        (*it) = 0;
}

void ITrigger::tick()
{
    if(test())
    {
        (*handler)();
        if(bFireOnce)
        {
            kill();
        }
    }
}

bool CTriggerTask::start() { return true; }
void CTriggerTask::stop() { ITrigger::triggerList.clear(); }
void CTriggerTask::update()
{
    PROFILE("Trigger task");
    std::list< CMMPointer<ITrigger> >::iterator it, ite = ITrigger::triggerList.end(), itT;
    for(it = ITrigger::triggerList.begin(); it != ite; it++)
    {
        if((*it).isValid())
        {
            (*it)->tick();
        }
        else
        {
            itT = it;
            --it;
            ITrigger::triggerList.erase(itT);
        }
    }
}

}
