#ifndef _SYSTEM_VIDEOUPDATE_H_
#define _SYSTEM_VIDEOUPDATE_H_

#include "system/kernel.h"
#include "system/dator.h"

class CVideoUpdate : public ITask
{
public:
    CVideoUpdate();
    virtual ~CVideoUpdate();
    AUTO_SIZE;

    static int scrWidth, scrHeight, scrBPP;
    static CMMPointer< Dator<int> > screenWidth, screenHeight, screenBPP;

    bool start();
    void update();
    void stop();
};

#endif // _SYSTEM_VIDEOUPDATE_H_

