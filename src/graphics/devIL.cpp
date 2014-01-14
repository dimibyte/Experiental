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

#include "graphics/devIL.h"
#include "system/CLog.h"

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
        printf("DevIL error: %s %s! Ignoring...\n", strError, filename);
        CLog::get().write(LOG_CLIENT, "DevIL error: %s %s! Ignoring...\n", strError, filename);
        CLog::get().write(LOG_USER, "DevIL error: %s %s! Ignoring...\n", strError, filename);
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
