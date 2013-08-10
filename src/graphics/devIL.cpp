#include "graphics/devIL.h"

///CTexture

CTexture::CTexture() {
    ilInit();
    iluInit();
}

CTexture::~CTexture() {
}

//Загрузка текстур
void CTexture::LoadTexture(ILenum FileType, char *filename, TextureImage *texture) {
    //DevIL, загрузи файл
    ilLoad(FileType, filename);
    //Ошибки
    int err = ilGetError();
    if(err != IL_NO_ERROR) {
        const char* strError = iluErrorString(err);
        printf("DevIL error: %s\nIgnoring this error\n", strError);
    }
    //Получаем данные текстуры
    texture->width = ilGetInteger(IL_IMAGE_WIDTH);
    texture->height = ilGetInteger(IL_IMAGE_HEIGHT);
    texture->bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
    //Загружаем данные в нашу структуру
    texture->imageData = ilGetData();

    ilEnable(IL_CONV_PAL);

    //тип данных изображения
    unsigned int type = ilGetInteger(IL_IMAGE_FORMAT);

    //генерируем текстуру
    glGenTextures(1, &texture->texID);
    //привязываем к ID
    glBindTexture(GL_TEXTURE_2D, texture->texID);
    //привязываем mip-map
    gluBuild2DMipmaps(GL_TEXTURE_2D, texture->bpp, texture->width,
                      texture->height, type, GL_UNSIGNED_BYTE, texture->imageData);
    //качество
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void CTexture::FreeTexture(TextureImage *texture) {
    //?
}
