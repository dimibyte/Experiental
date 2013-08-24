#ifndef _SYSTEM_TESTTASK_H_
#define _SYSTEM_TESTTASK_H_

#include "system/kernel.h"

class COurTestTask : public ITask
{
public:
    bool start();
    void update();
    void stop();
    AUTO_SIZE;
};


#endif // _SYSTEM_TESTTASK_H_

