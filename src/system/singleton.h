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

#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <cassert>

namespace Experiental
{

template<typename T>
class Singleton
{
    static T* ms_singleton;
public:
    Singleton()
    {
        //assert(!ms_singleton);
        //use a cunning trick to get the singleton pointing to the start of
        //the whole, rather than the start of the Singleton part of the object
        //int offset = *((int*)(T*)1) - *((int*)(Singleton <T>*)(T*)1);
        //ms_singleton = (T*)((int*)this + offset);
    }
    ~Singleton()
    {
        assert(ms_singleton);
        ms_singleton = 0;
    }
    static void setSingleton(T* val)
    {
        ms_singleton = val;
    }
    static T& getSingleton()
    {
        assert(ms_singleton);
        return *ms_singleton;
    }
    static T* getSingletonPtr()
    {
        assert(ms_singleton);
        return ms_singleton;
    }
};

template<typename T> T* Singleton <T>::ms_singleton = 0;

}

#endif      //_SINGLETON_H_
