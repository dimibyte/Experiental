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
