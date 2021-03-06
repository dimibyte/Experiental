#ifndef _SYSTEM_GLOBALTIMER_H_
#define _SYSTEM_GLOBALTIMER_H_

#include "system/kernel.h"

namespace Experiental
{

class CGlobalTimer : public ITask
{
public:
    CGlobalTimer();
	virtual ~CGlobalTimer();
	AUTO_SIZE;

    static float dT;
    static unsigned long lastFrameIndex;
    static unsigned long thisFrameIndex;

    bool start();
    void update();
    void stop();

    void reset();
};

}

#endif      //_SYSTEM_GLOBALTIMER_H_
