#ifndef _GAME_TASKS_LOGO_H_
#define _GAME_TASKS_LOGO_H_

#include "system/kernel.h"

using namespace Experiental;

class CLogoTask : public ITask
{
public:
    bool start();
    void update();
    void stop();
    AUTO_SIZE;
};

#endif // _GAME_TASKS_LOGO_H_

