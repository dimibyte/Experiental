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

#include "graphics/openGL.h"
#include "globals.h"

namespace Experiental
{

bool initGL(int screenWidth, int screenHeight)
{
    glClearColor(0, 0, 0, 0);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /*
    int w = SCREEN_WIDTH;
    int h = SCREEN_HEIGHT;
    GLdouble size;
    GLdouble aspect = (GLdouble)SCREEN_WIDTH/(GLdouble)SCREEN_HEIGHT;
    size = (GLdouble)((w >= h) ? w : h) / 2.0;
    if (w <= h) {
        aspect = (GLdouble)h/(GLdouble)w;
        glOrtho(-size, size,-size*aspect, size*aspect,-100000.0, 100000.0);
    }
    else {
        aspect = (GLdouble)w/(GLdouble)h;
        glOrtho(-size*aspect, size*aspect,-size, size,-100000.0, 100000.0);
    }
    */
    gluPerspective(45.0, (GLdouble)screenWidth/(GLdouble)screenHeight, 0.001, 1000.0);
    //glScaled(aspect, aspect, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glFlush();

    if(glGetError() != GL_NO_ERROR)
        return false;
    return true;
}

}
