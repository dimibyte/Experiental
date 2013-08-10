
/// Memory manager element
/// Элемент менеджера памяти


#ifndef _IMMOBJECT_H_
#define _IMMOBJECT_H_

#include <list>

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

#endif      //_IMMOBJECT_H_
