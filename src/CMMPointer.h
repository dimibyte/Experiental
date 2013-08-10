#ifndef _CMMPOINTER_H_
#define _CMMPOINTER_H_

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
    }
    //Assigning another smart pointer
    inline T& operator =(const CMMPointer<T> &p)
    {
        if(obj)
            obj->release();
        obj = p.obj;
        if(obj)
            obj->addRef();
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

#endif      //_CMMPOINTER_H_
