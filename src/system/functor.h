#ifndef _FUNCTOR_H_
#define _FUNCTOR_H_

#include "system/mmanager.h"

class Functor : public IMMObject
{
public:
    virtual void operator ()() = 0;
};

template<class T>
class ObjFunctor : public Functor
{
protected:
    T *obj;
    typedef void (T::*funcType)();
    funcType func;
public:
    AUTO_SIZE;

    ObjFunctor(T *o, funcType f)
    { obj = o; func = f; }

    void operator ()()
    { (obj->*func)(); }
};

template<class T>
class MMObjFunctor : public Functor
{
protected:
    CMMPointer<T> obj;
    typedef int (T::*funcType)();
    funcType func;
public:
    AUTO_SIZE;

    MMObjFunctor(T *o, funcType f)
    { obj = o; func = f; }

    int operator ()()
    { return (obj->*func)(); }
};

#endif      //_FUNCTOR_H_
