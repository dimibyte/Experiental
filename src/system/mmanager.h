
/// Memory manager element
/// Элемент менеджера памяти


#ifndef _IMMOBJECT_H_
#define _IMMOBJECT_H_

#include <list>
#include <cassert>

//define a quick macro to make things easier on derived classes
#define AUTO_SIZE unsigned long size(){ return sizeof(*this); }

class IMMObject
{
private:
    static std::list<IMMObject *> liveObjects;
    static std::list<IMMObject *> deadObjects;
    long refCount;
protected:
    IMMObject();
    virtual ~IMMObject();
public:
    void addRef();        // ? inline this function some how
    void release();     // ? inline this function some how
    static void collectGarbage();
    static void collectRemainingObjects(bool bEmitWarnings = false);
    virtual unsigned long size() = 0;
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

#endif      //_IMMOBJECT_H_
