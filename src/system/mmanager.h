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

/// Memory manager element
/// Элемент менеджера памяти


#ifndef _IMMOBJECT_H_
#define _IMMOBJECT_H_

#include <list>
#include <cassert>
#include <stdlib.h>

//define a quick macro to make things easier on derived classes
#define AUTO_SIZE unsigned long size(){ return sizeof(*this); }

class IMMObject
{
private:
    static IMMObject * liveObjects;
    static IMMObject * deadObjects;
    IMMObject *nextObject;
    IMMObject *prevObject;
    long refCount;
    bool bIsStackAllocated;
    static std::list<IMMObject*> heapObjects;
protected:
    IMMObject();
    virtual ~IMMObject();
public:
    void addRef();        // ? inline this function some how
    void release();     // ? inline this function some how
    static void collectGarbage();
    static void collectRemainingObjects(bool bEmitWarnings = false);
    virtual unsigned long size() = 0;
    void *operator new(size_t objsize);
    void operator delete(void* obj);
};

///Smart pointer
template<class T>
class CMMPointer
{
protected:
    T* obj;
public:
    //Constructors - basic
    CMMPointer()
    {
        obj = 0;
    }
    //Constructing with a pointer
    CMMPointer(T *o)
    {
        obj = 0;
        *this = o;
    }
    //Constructiong with another smart pointer (copy constructor)
    CMMPointer(const CMMPointer<T> &p)
    {
        obj = 0;
        *this = p;
    }
    //Destructor
    ~CMMPointer()
    {
        if(obj)
            obj->release();
    }

    //Assignment operators - assigning a plain pointer
    inline T& operator=(T *o)
    {
        if(obj)
            obj->release();
        obj = o;
        if(obj)
            obj->addRef();
        return *obj;
    }
    //Assigning another smart pointer
    inline T& operator =(const CMMPointer<T> &p)
    {
        if(obj)
            obj->release();
        obj = p.obj;
        if(obj)
            obj->addRef();
        return *obj;
    }

    //Access as a reference
    inline T& operator *() const
    {
        assert(obj != 0 && "Tried to * on a NULL smart pointer");
        return *obj;
    }
    //Access as a pointer
    inline T* operator ->() const
    {
        assert(obj != 0 && "Tried to -> on a NULL smart pointer");
        return obj;
    }

    //Conversion - allow the smart pointer to be automatically converted to type T*
    inline operator T*() const
    {
        return obj;
    }

    inline bool isValid() const
    {
        return (obj != 0);
    }
    inline bool operator !()
    {
        return !(obj);
    }
    inline bool operator ==(const CMMPointer<T> &p) const
    {
        return (obj == p.obj);
    }
    inline bool operator ==(const T* o) const
    {
        return (obj == o);
    }
};

template<class T, int i>
class CMMBlob : public IMMObject
{
protected:
    T buffer[i];
public:
    inline T& operator [](int index)
    {
        assert(index < i);// && "Bad index on CMMBlob::[]");
        return buffer[index];
    }
    inline operator T*()
    {
        return buffer;
    }
    AUTO_SIZE;
};

template<class T>
class CMMDynamicBlob : public IMMObject
{
protected:
    unsigned long dataSize;
    T *buffer;
public:
    inline T& operator [](int index)
    {
        assert(((index >= 0) && ((unsigned int)index < dataSize)));// && "Bad index on CMMDynamicBlob::[]");
        return buffer[index];
    }
    inline operator T*()
    {
        return buffer;
    }

    CMMDynamicBlob(unsigned long size)
    {
        dataSize = size;
        buffer = new T[size];
        //assert(buffer != 0 && "DynamicBlob buffer could not be created - out of memory?");
    }
    ~CMMDynamicBlob()
    {
        if(buffer)
            delete[] buffer;
    }

    unsigned long size()
    {
        return dataSize + sizeof(this);
    }
    inline unsigned long blobSize()
    {
        return dataSize;
    }
};

#endif      //_IMMOBJECT_H_
