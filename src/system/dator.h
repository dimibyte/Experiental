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

///A dator is an object which wraps a data member
//Dators will be useful later on for scripting, but right now, we're going to use them for our settings mechanism.

#ifndef _DATOR_H_
#define _DATOR_H_

#include <string>
#include <sstream>

#include "system/mmanager.h"

class BaseDator : public IMMObject
{
protected:
    BaseDator();
    BaseDator(BaseDator &b);
public:
    virtual BaseDator &operator =(std::string &s) = 0;
    virtual BaseDator &operator +=(std::string &s) = 0;
    virtual BaseDator &operator -=(std::string &s) = 0;
    virtual bool operator ==(std::string &s) = 0;
    virtual bool operator !=(std::string &s) = 0;

    virtual bool hasMultipleValues() = 0;

    virtual operator std::string() = 0;
};

template<class T>
class Dator : public BaseDator
{
protected:
    T& target;
    T toVal(std::string &s)
    {
        std::stringstream str;
        str.unsetf(std::ios::skipws);
        str<<s;
        T res;
        str>>res;
        return res;
    }
    std::string toString(T &val)
    {
        std::stringstream str;
        str.unsetf(std::ios::skipws);
        str<<val;
        std::string res;
        str>>res;
        return res;
    }
public:
    Dator(T& t) : target(t) {}
    BaseDator &operator =(std::string &input)
    {   target = toVal(input); return *this;    }
    BaseDator &operator +=(std::string &input)
    {   target += toVal(input); return *this;    }
    BaseDator &operator -=(std::string &input)
    {   target -= toVal(input); return *this;    }
    bool operator ==(std::string &s)
    {   return (s == (std::string)(*this));     }
    bool operator !=(std::string &s)
    {   return (s != (std::string)(*this));     }
    operator std::string()
    {   return toString(target);    }

    bool hasMultipleValues()
    {   return false;   }

    AUTO_SIZE;
};

template<class T>
class ListDator : public BaseDator
{
protected:
    std::list<T> &values;
    T toVal(std::string &s)
    {
        std::stringstream str;
        str.unsetf(std::ios::skipws);
        str<<s;
        T res;
        str>>res;
        return res;
    }
    std::string toString(T &val)
    {
        std::stringstream str;
        str.unsetf(std::ios::skipws);
        str<<val;
        std::string res;
        str>>res;
        return res;
    }
public:
    ListDator(std::list<T> &v) : values(v) {}
    BaseDator &operator =(std::string &s)
    {   values.clear(); values.push_back(toVal(s)); return *this;    }
    BaseDator &operator +=(std::string &s)
    {   values.push_back(toVal(s)); return *this;    }
    BaseDator &operator -=(std::string &s)
    {   values.remove(toVal(s)); return *this;    }
    bool operator ==(std::string &s)
    {   return (std::find(values.begin(), values.end(), toVal(s)) != values.end());     }
    bool operator !=(std::string &s)
    {   return !((*this) == s);     }

    operator std::string()
    {   return toString(values.back());    }
    operator std::list<T>&()
    {   return values;  }

    bool hasMultipleValues()
    {   return true;   }

    AUTO_SIZE;
};

#endif      //_DATOR_H_
