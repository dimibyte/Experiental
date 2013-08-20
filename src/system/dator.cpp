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

/* Examples, how to use dator */
/*/

//we can have a variable of pretty much any type - let's pick int for simplicity
int someValue;
//we can then create a dator bound to it like this
CMMPointer< Dator<int> > dator=new Dator<int>(someValue);
//if we then assign to the dator...
(*dator)=std::string("5");
//the value of someValue should now be 5.

//using ListDators is pretty similar, as I said earlier
std::list<int> someValues;
CMMPointer< ListDator<int> > listDator=new ListDator(someValues);
(*listDator)=std::string("5");
(*listDator)+=std::string("6");
(*listDator)-=std::string("5");
//someValues should now have the single entry 6.

/*/

#include "system/dator.h"

BaseDator::BaseDator()
{
}

BaseDator::BaseDator(BaseDator &b)
{
    (*this) = b;
}
