///Basic startup logo

#include "game/tasks/logo.h"
#include "system/inputTask.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "graphics/devIL.h"
#include "system/videoUpdate.h"
#include "system/CLog.h"

TextureImage textures[2];
CTexture *Texture;

///OrthoMode
//Переключение в 2D режим
void OrthoMode(int left, int top, int right, int bottom) {
    //Эта функция принимает координаты квадрата для нашего 2D экрана.

    //Переключаемся на матрицу проекции, чтобы перейти в режим ortho, не perspective
    glMatrixMode(GL_PROJECTION);
    //Входим в новую матрицу, чтобы потом выйти из неё, для возвращения в режим перспективы
    glPushMatrix();
    //Сбросим нашу текущую матрицу
    glLoadIdentity();
    //Передаём OpenGL экранные координаты. Лево, право, низ, верх.
    //Последние 2 параметра - ближняя и дальняя плоскости.
    glOrtho(left, right, bottom, top, 0, 1);
    //Переключаемся в modelview, чтобы рендерить общую картинку
    glMatrixMode(GL_MODELVIEW);
    //Обнулим текущую матрицу
    glLoadIdentity();
}

///PerspectiveMode
//Возвращает нас из 2D режима в 3D.
void PerspectiveMode() {
    //Входим в режим матрицы проекции
    glMatrixMode(GL_PROJECTION);
    //Выходим из последней матрицы, возвращаясь в матрицу с режимом перспективы.
    glPopMatrix();
    //Возвращаемся в матрицу моделей
    glMatrixMode(GL_MODELVIEW);

    //Теперь мы должны быть в нормальном 3D режиме с перспективой.
}

bool CLogoTask::start()
{
    Texture = new CTexture();
    ilEnable(IL_CONV_PAL);
    Texture->LoadTexture(IL_PNG, (char*)"Logo1.png", &textures[0]);
    //Texture->LoadTexture(IL_PNG, "Logo2.png", &textures[1]);

    glClearColor(.0f, .0f, .0f, .0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LEQUAL);
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glViewport(0, 0, 1280, 720);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)1280/(GLfloat)720, .001f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if(glGetError() != GL_NO_ERROR)
        return false;
    return true;
}

void CLogoTask::update()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0, 0, -1 , 0, 0, 1 , 0, 1, 0);
    OrthoMode(0, 0, 1280, 720);

    glColor4f(1, 1, 1, 1);
    glDisable(GL_DEPTH_TEST);
    //биндим текстуру маски к нашему 2D квадрату
    glBindTexture(GL_TEXTURE_2D, textures[0].texID);
    //Отображаем 2D квадрат с маской
    glBegin(GL_QUADS);
        //Находясь в 2D режиме, мы используем glVertex2f(), передавая не вершины, а экранные координаты.

        //Верхняя левая точка
        glTexCoord2f(0.0f, 1.0f);   glVertex2f(0, 720);
        //Нижняя левая
        glTexCoord2f(0.0f, 0.0f);   glVertex2f(0, 0);
        //Нижняя правая
        glTexCoord2f(1.0f, 0.0f);   glVertex2f(1280, 0);
        //Верхняя правая
        glTexCoord2f(1.0f, 1.0f);   glVertex2f(1280, 720);
    glEnd();
    glEnable(GL_DEPTH_TEST);

    PerspectiveMode();

    if(CInputTask::mouseDown(SDL_BUTTON_LEFT))
    {
        CKernel::getSingleton().killAllTasks();
        CLog::get().write(LOG_USER, "Exiting...");
    }
}

void CLogoTask::stop()
{

}
