
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
