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

#ifndef _SYSTEM_TRIGGERS_H_
#define _SYSTEM_TRIGGERS_H_

#include "system/kernel.h"
#include "system/functor.h"
#include <list>
#include "system/inputTask.h"

namespace Experiental
{

///Main class
class ITrigger : public IMMObject
{
public:
    ITrigger(Functor *h, bool fo);
    virtual ~ITrigger();

    void kill();

protected:
    CMMPointer<Functor> handler;
    bool bFireOnce;

    virtual bool test() = 0;

    static std::list< CMMPointer<ITrigger> > triggerList;

    friend class CTriggerTask;

private:
    void tick();
};

///Task
class CTriggerTask : public ITask
{
public:
    bool start();
    void update();
    void stop();
    AUTO_SIZE;
};

///Derived classes
template<class T>
class CEqualsTrigger : public ITrigger
{
protected:
    T &subject;
    T object;
public:
    CEqualsTrigger(T& s, T o, Functor *h, bool fo = true) : ITrigger(h, fo), subject(s)
    {
        object = o;
    }

    bool test() { return (subject == object); }

    AUTO_SIZE;
};

template<class T>
class CNotEqualsTrigger : public ITrigger
{
protected:
    T &subject;
    T object;
public:
    CNotEqualsTrigger(T& s, T o, Functor *h, bool fo = true) : ITrigger(h, fo), subject(s)
    {
        object = o;
    }

    bool test() { return !(subject == object); }

    AUTO_SIZE;
};

template<class T>
class CLessTrigger : public ITrigger
{
protected:
    T &subject;
    T object;
public:
    CLessTrigger(T& s, T o, Functor *h, bool fo = true) : ITrigger(h, fo), subject(s)
    {
        object = o;
    }

    bool test() { return (subject < object); }

    AUTO_SIZE;
};

template<class T>
class CGreaterTrigger : public ITrigger
{
protected:
    T &subject;
    T object;
public:
    CGreaterTrigger(T& s, T o, Functor *h, bool fo = true) : ITrigger(h, fo), subject(s)
    {
        object = o;
    }

    bool test() { return (subject > object); }

    AUTO_SIZE;
};

class CKeyTrigger : public ITrigger
{
public:
	CKeyTrigger(int keyCode, Functor *h) : ITrigger(h, false) { kc = keyCode; }
	AUTO_SIZE;
protected:
	int kc;
};

class CKeyDownTrigger : public CKeyTrigger
{
public:
	CKeyDownTrigger(int keyCode, Functor *h) : CKeyTrigger(keyCode, h) {}
	bool test(){ return CInputTask::keyDown(kc); }
};

class CKeyIsDownTrigger : public CKeyTrigger
{
public:
	CKeyIsDownTrigger(int keyCode, Functor *h) : CKeyTrigger(keyCode, h) {}
	bool test(){ return CInputTask::curKey(kc); }
};

class CKeyHoldTrigger : public CKeyTrigger
{
public:
	CKeyHoldTrigger(int keyCode, Functor *h) : CKeyTrigger(keyCode, h) {}
	bool test(){ return CInputTask::keyStillDown(kc); }
};

class CKeyIsUpTrigger : public CKeyTrigger
{
public:
	CKeyIsUpTrigger(int keyCode, Functor *h) : CKeyTrigger(keyCode, h) {}
	bool test(){ return !CInputTask::curKey(kc); }
};

class CKeyUpTrigger : public CKeyTrigger
{
public:
	CKeyUpTrigger(int keyCode, Functor *h) : CKeyTrigger(keyCode, h) {}
	bool test(){ return CInputTask::keyUp(kc); }
};

/* the TRIGGER_CLASS macro - uncomment this section to use it

#define TRIGGER_CLASS(classname, test)	template<class T> \
					class classname : public ITrigger \
					{ \
					protected: \
						T &subject; T object; \
					public: \
						classname##(T& s,T o, Functor *h, bool fo=true) : ITrigger(h,fo), subject(s) { object=o; } \
						bool test(){return (##test##);} AUTO_SIZE; };

//all triggers through trigger_class have 'subject' and 'object' as names for the two test parameters:
TRIGGER_CLASS(CGreaterEqualTrigger, subject>=object);
TRIGGER_CLASS(CLessEqualTrigger, subject<=object);
//of course, you don't have to use both of them:
TRIGGER_CLASS(CTrueTrigger, subject);
TRIGGER_CLASS(CFalseTrigger, !subject);
//you can also construct more complex functions:
TRIGGER_CLASS(CMagnitudeGreaterTrigger, fabs(subject)>fabs(object));
//and so on. Of course, the more complex the function you set up, the more limited the use of the trigger will be.

*/

}

#endif // _SYSTEM_TRIGGERS_H_
