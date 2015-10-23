/*Author: Keith Harryman
 * Program Nam: hud.h
 * Purpose: To show start screen, and score screen:
 * */

#include <GL/gl.h>
#include <GL/glu.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <GL/glx.h>

#include <GL/glut.h>
#include <string>

using namespace std;


class Hud{
  private:
  int xres;
  int yres;  
  public:
   bool is_show_welcome;
   Hud(const int in_xres, const int in_yres);
   void showWelcome(int in_high_score);
   void showScore(int in_score1, int in_score2);
   void showCourtYard();
};


Hud::Hud(const int in_xres, const int in_yres){
    xres = in_xres;
    yres = in_yres;
    is_show_welcome=true;
    char fakeParam[] = "fake";
    char *fakeargv[] = { fakeParam, NULL };
    int fakeargc = 1;
    glutInit( &fakeargc, fakeargv );
}


void Hud::showCourtYard(){
      //DRAW OUTER RECTANGLE:
      glMatrixMode( GL_PROJECTION );
      glLoadIdentity();
      glOrtho( 0, xres, 0, yres, -1, 1);
      glMatrixMode( GL_MODELVIEW );
      glLoadIdentity();
      glTranslatef( 0.5, 0.5, 0 );
      float offset = 40;
      glColor3ub( 0, 255, 0 );
      glBegin(GL_LINE_LOOP);
      glVertex2f( 0+offset, 0+offset );
      glVertex2f( 0+offset, yres-offset );
      glVertex2f( xres-offset, yres-offset );
      glVertex2f( xres-offset, 0+offset );
      glEnd();

      //DRAW LINE THROUGH MIDDLE:
      glColor3ub( 0, 255, 0 );
      glBegin(GL_LINES);
      glVertex2f(xres/2,0+offset);
      glVertex2f(xres/2,yres-offset);
      glEnd();
}


void Hud::showWelcome(int in_high_score){
    //PRINT WELCOME MESSAGE:
    glPushMatrix();
    glColor3ub(0,255,255);
    glTranslatef(xres/2.0 - 50.0, yres/2.0, 0.0);
    glScalef(1/4.0, 1/4.0, 1/4.0);
    string str1="Welcome to Pong!";
    for(unsigned int i=0; i<str1.length(); i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN,str1[i]);
    }
    glPopMatrix();
    //--------------------------------------------------------

    //PRINT HIGH SCORE:
    glPushMatrix();
    glTranslatef(xres/2.0 - 50.0, yres/2.0 - 30.0, 0.0);
    glColor3ub(0,255,255);
    glScalef(1/8.0, 1/8.0, 1/8.0);
    string str2="Current high score is:";
    for(unsigned int i=0; i<str2.length(); i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN,str2[i]);
    }
    glPopMatrix();
    //--------------------------------------------------------
}


void Hud::showScore(int in_score1, int in_score2){    

    glColor3ub(255,255,255);

    //PRINT PLAYER 1'S SCORE:
    glPushMatrix();
    glTranslatef(40.0, yres - 30, 0.0);
    glScalef(1/8.0, 1/8.0, 1/8.0);
    string str1="Player 1 Score:" + in_score1;
    for(unsigned int i=0; i<str1.length(); i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN,str1[i]);
    }
    glPopMatrix();
    //--------------------------------------------------------

    //PRINT PLAYER 2'S SCORE:
    glPushMatrix();
    glTranslatef(xres/2.0, yres - 30, 0.0);
    glScalef(1/8.0, 1/8.0, 1/8.0);
    string str2="Player 2 Score:" + in_score2;
    for(unsigned int i=0; i<str2.length(); i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN,str2[i]);
    }
    glPopMatrix();
    //--------------------------------------------------------


}
