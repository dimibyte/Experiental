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

