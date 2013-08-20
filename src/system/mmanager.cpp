///A nice little base class to automatically memory-manage our objects.

#include "system/mmanager.h"

//a 'static initialiser' is needed in one of the source files
//to give the std::list a definetive presence
std::list<IMMObject *> IMMObject::liveObjects;
std::list<IMMObject *> IMMObject::deadObjects;

IMMObject::IMMObject()
{
    liveObjects.push_back(this);
    refCount = 0;
}

IMMObject::~IMMObject()
{
    //We add an empty virtual destructor to make sure
    //that the destructors in derived classes work properly.
}

void IMMObject::addRef()
{
    ++refCount;
}

void IMMObject::release()
{
    --refCount;
    if(refCount <= 0)
    {
        liveObjects.remove(this);       //TODO: Object should store some kind of iterator allowing to remove it directly.
        deadObjects.push_back(this);
    }
}

void IMMObject::collectGarbage()
{
    for(std::list<IMMObject *>::iterator it = deadObjects.begin(); it != liveObjects.end(); it++)
    {
        delete (*it);
    }
    deadObjects.clear();
}

void IMMObject::collectRemainingObjects(bool bEmitWarnings)
{
    collectGarbage();
    for(std::list<IMMObject *>::iterator it = liveObjects.begin(); it !=liveObjects.end(); it++)
    {
        IMMObject *o = (*it);
        if(bEmitWarnings)
        {
            //log some kind of error message here
        }
        delete o;
    }
    liveObjects.clear();
}
