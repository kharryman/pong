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
Game game;
Player p1;
Player p2;

//Idea:
//Maybe use command line arguments to
//set player1 and player2 names
//i.e. ./pong name1 name2
int main(int argc, char** argv)
{
  initXWindows();
  init_opengl();
  
  //init(&game);
  srand(time(NULL));
  //clock_gettime(CLOCK_REALTIME, &timePause);
  //clock_gettime(CLOCK_REALTIME, &timeStart);
  //set_mouse_position(100,100);
  int done=0;
  while (!done) {
  while (XPending(dpy)) {
    XEvent e;
    XNextEvent(dpy, &e);
    check_resize(&e);
    //check_mouse(&e, &game);
    done = check_keys(&e);
  }
  // clock_gettime(CLOCK_REALTIME, &timeCurrent);
  // timeSpan = timeDiff(&timeStart, &timeCurrent);
  // timeCopy(&timeStart, &timeCurrent);
  // physicsCountdown += timeSpan;
  // while (physicsCountdown >= physicsRate) {
  //   physics(&game);
  //   physicsCountdown -= physicsRate;
  // }
  render(&game);
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
 

  //-------------------------------------------------------------------------
  //Draw the ship
  // glColor3fv(g->ship.color);
  // glPushMatrix();
  // glTranslatef(g->ship.pos[0], g->ship.pos[1], g->ship.pos[2]);
  // //float angle = atan2(ship.dir[1], ship.dir[0]);
  // glRotatef(g->ship.angle, 0.0f, 0.0f, 1.0f);
  // glBegin(GL_TRIANGLES);
  // //glVertex2f(-10.0f, -10.0f);
  // //glVertex2f(  0.0f, 20.0f);
  // //glVertex2f( 10.0f, -10.0f);
  // glVertex2f(-12.0f, -10.0f);
  // glVertex2f(  0.0f, 20.0f);
  // glVertex2f(  0.0f, -6.0f);
  // glVertex2f(  0.0f, -6.0f);
  // glVertex2f(  0.0f, 20.0f);
  // glVertex2f( 12.0f, -10.0f);
  // glEnd();
  // glColor3f(1.0f, 0.0f, 0.0f);
  // glBegin(GL_POINTS);
  // glVertex2f(0.0f, 0.0f);
  // glEnd();
  // glPopMatrix();
  // if (keys[XK_Up] || g->mouseThrustOn) {
  //   int i;
  //   //draw thrust
  //   Flt rad = ((g->ship.angle+90.0) / 360.0f) * PI * 2.0;
  //   //convert angle to a vector
  //   Flt xdir = cos(rad);
  //   Flt ydir = sin(rad);
  //   Flt xs,ys,xe,ye,r;
  //   glBegin(GL_LINES);
  //   for (i=0; i<16; i++) {
  //     xs = -xdir * 11.0f + rnd() * 4.0 - 2.0;
  //     ys = -ydir * 11.0f + rnd() * 4.0 - 2.0;
  //     r = rnd()*40.0+40.0;
  //     xe = -xdir * r + rnd() * 18.0 - 9.0;
  //     ye = -ydir * r + rnd() * 18.0 - 9.0;
  //     glColor3f(rnd()*.3+.7, rnd()*.3+.7, 0);
  //     glVertex2f(g->ship.pos[0]+xs,g->ship.pos[1]+ys);
  //     glVertex2f(g->ship.pos[0]+xe,g->ship.pos[1]+ye);
  //   }
  //   glEnd();
  // }
  // //-------------------------------------------------------------------------
  // //Draw the asteroids
  // {
  //   Asteroid *a = g->ahead;
  //   while (a) {
  //     //Log("draw asteroid...\n");
  //     glColor3fv(a->color);
  //     glPushMatrix();
  //     glTranslatef(a->pos[0], a->pos[1], a->pos[2]);
  //     glRotatef(a->angle, 0.0f, 0.0f, 1.0f);
  //     glBegin(GL_LINE_LOOP);
  //     //Log("%i verts\n",a->nverts);
  //     for (int j=0; j<a->nverts; j++) {
  //       glVertex2f(a->vert[j][0], a->vert[j][1]);
  //     }
  //     glEnd();
  //     //glBegin(GL_LINES);
  //     //  glVertex2f(0,   0);
  //     //  glVertex2f(a->radius, 0);
  //     //glEnd();
  //     glPopMatrix();
  //     glColor3f(1.0f, 0.0f, 0.0f);
  //     glBegin(GL_POINTS);
  //     glVertex2f(a->pos[0], a->pos[1]);
  //     glEnd();
  //     a = a->next;
  //   }
  // }
  //-------------------------------------------------------------------------
  //Draw the bullets
  // {
  //   Bullet *b = g->bhead;
  //   while (b) {
  //     //Log("draw bullet...\n");
  //     glColor3f(1.0, 1.0, 1.0);
  //     glBegin(GL_POINTS);
  //     glVertex2f(b->pos[0],      b->pos[1]);
  //     glVertex2f(b->pos[0]-1.0f, b->pos[1]);
  //     glVertex2f(b->pos[0]+1.0f, b->pos[1]);
  //     glVertex2f(b->pos[0],      b->pos[1]-1.0f);
  //     glVertex2f(b->pos[0],      b->pos[1]+1.0f);
  //     glColor3f(0.8, 0.8, 0.8);
  //     glVertex2f(b->pos[0]-1.0f, b->pos[1]-1.0f);
  //     glVertex2f(b->pos[0]-1.0f, b->pos[1]+1.0f);
  //     glVertex2f(b->pos[0]+1.0f, b->pos[1]-1.0f);
  //     glVertex2f(b->pos[0]+1.0f, b->pos[1]+1.0f);
  //     glEnd();
  //     b = b->next;
  //   }
  // }
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
   XStoreName(dpy, win, "CS335 - Asteroids template");
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


