#ifndef _CMMBLOB_H_
#define _CMMBLOB_H_

#include <cassert>
#include "IMMObject.h"

template<class T, int i>
class CMMBlob : public IMMObject
{
protected:
    T buffer[i];
public:
    inline T& operator [](int index)
    {
        assert(index < i && "Bad index on CMMBlob::[]");
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
        assert(index<dataSize && "Bad index on CMMDynamicBlob::[]");
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
        assert(buffer != 0 && "DynamicBlob buffer could not be created - out of memory?");
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

#endif      //_CMMBLOB_H_
