#include "testTask.h"
#include "system/inputTask.h"
#include <GL/gl.h>

namespace Experiental
{

COurTestTask::COurTestTask()
{
}

bool COurTestTask::start()
{
    return true;
}

void COurTestTask::update()
{
    //glClear(GL_COLOR_BUFFER_BIT);
    if(CInputTask::mouseDown(SDL_BUTTON_LEFT))
        CKernel::getSingleton().killAllTasks();
}

void COurTestTask::stop()
{
}

}
