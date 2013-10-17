///Basic startup logo

#include "game/tasks/logo.h"
#include "system/inputTask.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "graphics/devIL.h"
#include "system/videoUpdate.h"

TextureImage textures[2];
CTexture *Texture;

///OrthoMode
//Perekljuchenie v 2D rezhim
void OrthoMode(int left, int top, int right, int bottom) {
    //Eta funkcija prinimaet koordinati kvadrata dlja nashego 2D ekrana.

    //Prekeljuchaemsja na matricu projekcii, chtobi perejti v rezhim ortho, ne perspective
    glMatrixMode(GL_PROJECTION);
    //Vhodim v novuju matricu, chtobi potom vijti iz nejo, dlja vozvrashenie v rezhim perspektivy
    glPushMatrix();
    //Sbrosim nashu tekushuju matricu
    glLoadIdentity();
    //Peredadajom OpenGL ekrannie koordinaty. Levo, pravo, niz, verh.
    //Poslednie 2  parametra - blizhnjaja i daljnjaja ploskosti.
    glOrtho(left, right, bottom, top, 0, 1);
    //Perkljuchaemsja v modelview, chtobi renderitj obshjuju kartinku
    glMatrixMode(GL_MODELVIEW);
    //Obnulim tekushuju matricu
    glLoadIdentity();
}

///PerspectiveMode
//Vozvrashaet nas iz 2D rezhima v 3D.
void PerspectiveMode() {
    //Vhodim v rezhim matricy projekcii
    glMatrixMode(GL_PROJECTION);
    //Vyhodim iz poslednej matricy, vozvrashajasjv matricu s rezhimom perspektivy.
    glPopMatrix();
    //Vozvrashaemsja v matricu modelej
    glMatrixMode(GL_MODELVIEW);

    //Teperj my dolzhny bytj v normaljnom 3D rezhime s perspektivoj.
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
    //bindim teksturu maski k nacshemu 2D kvadratu
    glBindTexture(GL_TEXTURE_2D, textures[0].texID);
    //Otobrozhaem 2D kvadrat s maskoj
    glBegin(GL_QUADS);
        //Nahodjasj v 2D rezime, my ispoljzujem glVertex2f(), peredavaja ne vershiny, a ekrannye koordinaty.

        //Verhnjaja levaja tochka
        glTexCoord2f(0.0f, 1.0f);   glVertex2f(0, 0);
        //Nizhnjaja levaja
        glTexCoord2f(0.0f, 0.0f);   glVertex2f(0, CVideoUpdate::scrWidth);
        //Nizhnjaja pravaja
        glTexCoord2f(1.0f, 0.0f);   glVertex2f(CVideoUpdate::scrWidth, CVideoUpdate::scrHeight);
        //Verhnjaja pravaja
        glTexCoord2f(1.0f, 1.0f);   glVertex2f(CVideoUpdate::scrWidth, 0);
    glEnd();
    glEnable(GL_DEPTH_TEST);

    PerspectiveMode();

    if(CInputTask::mouseDown(SDL_BUTTON_LEFT))
        CKernel::getSingleton().killAllTasks();
}

void CLogoTask::stop()
{

}
