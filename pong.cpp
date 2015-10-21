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

#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

using namespace std;
int width = 640;
int height = 480;
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

  GLFWwindow* window;
  
  if(!glfwInit()) {
    return(-1);
  }
  window = glfwCreateWindow(width, height, "Pong", NULL, NULL);

  if(!window) {
    glfwTerminate();
    return(-1);
  }
  glfwMakeContextCurrent(window);


  while(!glfwWindowShouldClose(window))
  {
    /* Render */
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    //Paddle 1 
    //glRectf(x1, y1, x2, y2)
    glRectf(p1.posX1, p1.posY1, p1.posX2, p1.posY2);

    //Paddle 2
    glRectf(-0.6f, -0.3f, -0.5f, -0.8f);
    
    glfwSetKeyCallback(window, key_callback);

    glfwSwapBuffers(window);

    glfwPollEvents();
  
  }

  glfwTerminate();
  cout << "Hello World";
  return 0;
 }

 void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

  
  switch(key) {
    case 87:
      p1.posY1 += 0.05;
      p1.posY2 += 0.05;
      break;
    case 83:
      p1.posY1 -= 0.05;
      p1.posY2 -= 0.05;
      break;
    default:
      break;
  }
  cout << key << endl;
  

 }