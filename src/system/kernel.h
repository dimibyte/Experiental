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

#ifndef _SYSTEM_KERNEL_H_
#define _SYSTEM_KERNEL_H_

#include "system/mmanager.h"
#include "system/singleton.h"

class ITask : public IMMObject
{
public:
    ITask();
    virtual bool start() = 0;
    virtual void onSuspend() {}
    virtual void update() = 0;
    virtual void onResume() {}
    virtual void stop() = 0;

    bool canKill;
    long priority;
};

class CKernel : public Singleton<CKernel>
{
public:
    CKernel();
    virtual ~CKernel();

    int execute();

    bool addTask(CMMPointer<ITask> &t);
    void suspendTask(CMMPointer<ITask> &t);
    void resumeTask(CMMPointer<ITask> &t);
    void removeTask(CMMPointer<ITask> &t);
    void killAllTasks();

protected:
    std::list< CMMPointer<ITask> > taskList;
    std::list< CMMPointer<ITask> > pausedTaskList;
};

#endif      //_SYSTEM_KERNEL_H_
