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

#ifndef _GRAPHICS_OPENGL_H_
#define _GRAPHICS_OPENGL_H_

#ifdef _WIN64
#ifndef POINTER_64
#define POINTER_64 __ptr64
#endif
#endif  //_WIN64

#include "system/SDL.h"
#include <GL/glu.h>

bool initGL(int screenWidth, int screeHeight);

#endif      //_GRAPHICS_INIT_H_
