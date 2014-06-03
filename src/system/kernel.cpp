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

#include "system/kernel.h"
#include "system/SDL.h"
#include "system/profiler.h"
#include <list>
#include <algorithm>

namespace Experiental
{

ITask::ITask()
{
    canKill = false;
    priority = 5000;
}

CKernel::CKernel()
{
    SDL_Init(0);
    SDLNet_Init();
}

CKernel::~CKernel()
{
    SDLNet_Quit();
    SDL_Quit();
}

int CKernel::execute()
{
    while(!taskList.empty())
    {
        {
            PROFILE("Kernel task loop");

            std::list< CMMPointer<ITask> >::iterator it, thisIt;
            for(it = taskList.begin(); it != taskList.end(); )
            {
                ITask *t = (*it);
                ++it;
                if(!t->canKill)
                    t->update();
            }
            /*//loop again to suspend/resume tasks
            for(it = taskList.begin(); it != taskList.end(); )
            {
                ITask *t = (*it);
                thisIt = it; ++it;
                if(t->on)
                {
                    t->stop();
                    taskList.erase(thisIt);
                    t = 0;
                }
            }*/
            //loop again to remove dead tasks
            for(it = taskList.begin(); it != taskList.end(); )
            {
                ITask *t = (*it);
                thisIt = it; ++it;
                if(t->canKill)
                {
                    t->stop();
                    taskList.erase(thisIt);
                    t = 0;
                }
            }
            IMMObject::collectGarbage();
        }
//#ifdef DEBUG
 //       CProfileSample::output();
//#endif
    }
    return 0;
}

bool CKernel::addTask(const CMMPointer<ITask> &t)
{
    if(!t->start())
        return false;

    //keep the order of priorities straight
    std::list< CMMPointer<ITask> >::iterator it;
    for(it = taskList.begin(); it != taskList.end(); ++it)
    {
        CMMPointer<ITask> &comp = (*it);
        if(comp->priority > t->priority)
            break;
    }
    taskList.insert(it, t);
    return true;
}

void CKernel::suspendTask(CMMPointer<ITask> &t)
{
    //check that this task is in our list - we don't want to suspend
    //a task that isn't running
    if(std::find(taskList.begin(), taskList.end(), t) != taskList.end())
    {
        t->onSuspend();
        taskList.remove(t);
        pausedTaskList.push_back(t);
    }
}

void CKernel::resumeTask(CMMPointer<ITask> &t)
{
    if(std::find(pausedTaskList.begin(), pausedTaskList.end(), t) != pausedTaskList.end())
    {
        t->onResume();
        pausedTaskList.remove(t);
        //keep the order of priorities straight
        std::list< CMMPointer<ITask> >::iterator it;
        for(it = taskList.begin(); it != taskList.end(); ++it)
        {
            CMMPointer<ITask> &comp = (*it);
            if(comp->priority > t->priority)
                break;
        }
        taskList.insert(it, t);
    }
}

void CKernel::removeTask(CMMPointer<ITask> &t)
{
    if(std::find(taskList.begin(), taskList.end(), t) != taskList.end())
    {
        t->canKill = true;
    }
}

void CKernel::killAllTasks()
{
    for(std::list< CMMPointer<ITask> >::iterator it = taskList.begin(); it != taskList.end(); ++it)
    {
        (*it)->canKill = true;
    }
}

}
