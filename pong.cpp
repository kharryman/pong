/**
 * filename: Pong.cpp
 * purpose: This is the main entry point of the
 * Pong game. Main() will instantiate a Game obj
 * which in return will instantiate all other 
 * game objects and begin the main game loop
 *
 * TODO:
 * Build class definitions
 * Bring in graphics implementation
 * Httpget functionality to post high scores to DB
 * 
 */
#include <iostream>

#include "game.h"
#include "player.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <GL/glx.h>

#include <GL/glut.h>
#include <string>

#include "keithH.cpp"
#include <ctime>
#include <time.h>


using namespace std;

//X Windows variables
Display *dpy;
Window win;
GLXContext glc;

void initXWindows(void);
void init_opengl(void);
void set_title(void);
void initXWindows(void);
void init_opengl(void);
void cleanupXWindows(void);
void check_resize(XEvent *e);
void check_mouse(XEvent *e, Game *game);
int check_keys(XEvent *e);
void init(Game *g);
void init_sounds(void);
void physics(Game *game);
void render(Game *game);
void set_mouse_position(int x, int y);
void show_mouse_cursor(const int onoff);


int keys[65536];
int xres = 640;
int yres = 480;
int interval = 1000 / 60;

int timeStart;
Game game;
Player p1;
Player p2;
Hud *hud;

//Idea:
//Maybe use command line arguments to
//set player1 and player2 names
//i.e. ./pong name1 name2
int main(int argc, char** argv)
{
  hud = new Hud(xres ,yres);
  initXWindows();
  init_opengl();
  
  //init(&game);
  srand(time(NULL));
  timeStart = 0;
  //clock_gettime(CLOCK_REALTIME, &timePause);
  //clock_gettime(CLOCK_REALTIME, &timeStart);
  //set_mouse_position(100,100);
  int done=0;
  time_t timeStart = time(NULL);
  while (!done) {
    while (XPending(dpy)) {
        XEvent e;
        XNextEvent(dpy, &e);
        check_resize(&e);
        //check_mouse(&e, &game);
        done = check_keys(&e);
    }
    render(&game);
    //KEITH HARRYMANS ADDITION TO MAIN:
    if (timeStart + 2.0 > time(NULL)){
        //PASS showWelcome the high score:
        hud->showWelcome(0);
        hud->is_show_welcome = true;
    }
    else{
        hud->showScore(p1.getScore(), p2.getScore());
        hud->showCourtYard();
        hud->is_show_welcome = false;
    }
    //---------------------------------------------------
  glXSwapBuffers(dpy, win);
  }
  cleanupXWindows();
return 0;
}

void render(Game *g)
{
  
  glClear(GL_COLOR_BUFFER_BIT);
  

  glColor3f(1.0f, 1.0f, 1.0f);

   //TODO use player.getX, .getY etc
   //for rendering
   
   //Paddle 1 
   //glRectf(x1, y1, x2, y2)
   glRectf(0.6f, 0.3f, 0.5f, 0.8f);

   //Paddle 2
   glRectf(-0.6f, -0.3f, -0.5f, -0.8f);
 

}

void cleanupXWindows(void)
{
XDestroyWindow(dpy, win);
XCloseDisplay(dpy);
}

    
 void setup_screen_res(const int w, const int h)
 {
  xres = w;
  yres = h;
 }

 void initXWindows(void)
 {
  GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
  //GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
  XSetWindowAttributes swa;
  setup_screen_res(xres, yres);
  dpy = XOpenDisplay(NULL);
  if (dpy == NULL) {
    std::cout << "\n\tcannot connect to X server" << std::endl;
    exit(EXIT_FAILURE);
  }
  Window root = DefaultRootWindow(dpy);
  XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
  if (vi == NULL) {
    std::cout << "\n\tno appropriate visual found\n" << std::endl;
    exit(EXIT_FAILURE);
  } 
  Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
  swa.colormap = cmap;
  swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
    PointerMotionMask | MotionNotify | ButtonPress | ButtonRelease |
    StructureNotifyMask | SubstructureNotifyMask;
  win = XCreateWindow(dpy, root, 0, 0, xres, yres, 0,
      vi->depth, InputOutput, vi->visual,
      CWColormap | CWEventMask, &swa);
  set_title();
  glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
  glXMakeCurrent(dpy, win, glc);
  //show_mouse_cursor(0);
 }

void set_title(void)
 {
   //Set the window title bar.
   XMapWindow(dpy, win);
   XStoreName(dpy, win, "CS335 - PONG!");
 }



 void reshape_window(int width, int height)
 {
  //window has been resized.
  setup_screen_res(width, height);
  //
  glViewport(0, 0, (GLint)width, (GLint)height);
  glMatrixMode(GL_PROJECTION); glLoadIdentity();
  glMatrixMode(GL_MODELVIEW); glLoadIdentity();
  glOrtho(0, xres, 0, yres, -1, 1);
  set_title();
 }

 void init_opengl(void)
 {
  //OpenGL initialization  


  glViewport(0, 0, xres, yres);
  //Initialize matrices
  glMatrixMode(GL_PROJECTION); glLoadIdentity();
  glMatrixMode(GL_MODELVIEW); glLoadIdentity();
  //This sets 2D mode (no perspective)
  glOrtho(0, xres, 0, yres, -1, 1);
  //
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_FOG);
  glDisable(GL_CULL_FACE);
  //
  //Clear the screen to black
  glClearColor(0.0, 0.0, 0.0, 1.0);
  //Do this to allow fonts
  glEnable(GL_TEXTURE_2D);
  //initialize_fonts();
 }

 void check_resize(XEvent *e)
 {
  //The ConfigureNotify is sent by the
  //server if the window is resized.
  if (e->type != ConfigureNotify)
    return;
  XConfigureEvent xce = e->xconfigure;
  if (xce.width != xres || xce.height != yres) {
    //Window size did change.
    reshape_window(xce.width, xce.height);
  }
 }

int check_keys(XEvent *e)
{
//keyboard input?
static int shift=0;
int key = XLookupKeysym(&e->xkey, 0);
//Log("key: %i\n", key);
if (e->type == KeyRelease) {
  keys[key]=0;
  if (key == XK_Shift_L || key == XK_Shift_R)
    shift=0;
  return 0;
}
if (e->type == KeyPress) {
  //std::cout << "press" << std::endl;
  keys[key]=1;
  if (key == XK_Shift_L || key == XK_Shift_R) {
    shift=1;
    return 0;
  }
} else {
  return 0;
}
if (shift){}
switch(key) {
  case XK_Escape:
    return 1;
  case XK_f:
    break;
  case XK_s:
    break;
  case XK_Down:
    break;
  case XK_equal:
    break;
  case XK_minus:
    break;
}
return 0;
}


