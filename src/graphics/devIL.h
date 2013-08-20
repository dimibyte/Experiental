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

#ifndef _GRAPHICS_DEVIL_H_
#define _GRAPHICS_DEVIL_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

//#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glx.h>

#include <IL/il.h>
#include <IL/ilu.h>

typedef struct TextureImage {
    GLubyte *imageData;     //данные текстуры
    GLuint bpp;             //Байт за пиксель
    GLuint width, height;   //Ширина и высота
    GLuint texID;           //ID текстуры
}   TextureImage;

class CTexture {
public:
    CTexture();
    ~CTexture();

    void LoadTexture(ILenum FileType, char *filename, TextureImage *texture);
    void FreeTexture(TextureImage *texture);
};

#endif

