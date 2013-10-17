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

///A nice little base class to automatically memory-manage our objects.

#include "system/mmanager.h"
#include "system/CLog.h"
#include <string.h>         //memcpy
#include <algorithm>        //std::find

//a 'static initialiser' is needed in one of the source files
//to give the std::list a definetive presence
IMMObject *IMMObject::liveObjects = 0;
IMMObject *IMMObject::deadObjects = 0;
std::list<IMMObject *> IMMObject::heapObjects;
unsigned long IMMObject::heapUsage=0;

IMMObject::IMMObject()
{
    nextObject = prevObject = 0;
    refCount = 0;
    std::list<IMMObject*>::iterator it = std::find(heapObjects.begin(), heapObjects.end(), this);
    if(it == heapObjects.end())
    {
        bIsStackAllocated = true;
    }
    else
    {
        bIsStackAllocated = false;
        heapObjects.erase(it);
    }
    if(!bIsStackAllocated)
    {
        //start on the deadObjects list
        nextObject = deadObjects;
        if(deadObjects)
            deadObjects->prevObject = this;
        deadObjects = this;
    }
}

IMMObject::~IMMObject()
{
    //We add an empty virtual destructor to make sure
    //that the destructors in derived classes work properly.
}

void IMMObject::addRef()
{
    ++refCount;
    if(!bIsStackAllocated && (refCount == 1))
    {
        //move to the liveObjects list
        if(prevObject)
            prevObject->nextObject = nextObject;
        if(nextObject)
            nextObject->prevObject = prevObject;
        if(deadObjects == this)
            deadObjects = nextObject;
        prevObject = 0;
        nextObject = liveObjects;
        if(liveObjects)
            liveObjects->prevObject = this;
        liveObjects = this;
    }
}

void IMMObject::release()
{
    --refCount;
    if(!bIsStackAllocated && (refCount <= 0))
    {
        //remove self from liveObjects list
        if(prevObject)
            prevObject->nextObject = nextObject;
        if(nextObject)
            nextObject->prevObject = prevObject;
        if(liveObjects == this)
            liveObjects = nextObject;
        prevObject = 0;
        //add self to dead list
        nextObject = deadObjects;
        if(deadObjects)
            deadObjects->prevObject = this;
        deadObjects = this;
    }
}

void IMMObject::collectGarbage()
{
    while(deadObjects)
    {
        IMMObject *nObj = deadObjects->nextObject;
        delete deadObjects;
        deadObjects = nObj;
    }
}

void IMMObject::collectRemainingObjects(bool bEmitWarnings)
{
    collectGarbage();
    while(liveObjects)
    {
        IMMObject *o = liveObjects->nextObject;
        if(bEmitWarnings)
        {
            //copy the object to a temporary buffer so that our '10 bytes' message doesn't
            //cause an access violation
            char szBuf[11] = {0};
            memset(szBuf, 0, 11);
            memcpy(szBuf, liveObjects, std::min(liveObjects->size(), (long unsigned int)10));
            CLog::get().write(LOG_APP, IDS_UNRELEASED_OBJECT, liveObjects, liveObjects->size(), szBuf);
        }
        delete liveObjects;
        liveObjects = o;
    }
}

void* IMMObject::operator new(size_t objsize)
{
    void *newObj = malloc(objsize);
    heapUsage+=objsize;
    heapObjects.push_back((IMMObject*)newObj);
    ((IMMObject*)newObj)->heapAllocSize=objsize;
    return newObj;
}

void IMMObject::operator delete(void* obj)
{
    if(!((IMMObject*)obj)->bIsStackAllocated)
    {
        heapUsage-=((IMMObject*)obj)->heapAllocSize;
        free(obj);
    }
}
