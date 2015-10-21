#include "player.h"
#include <string>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

using namespace std;

Player::Player() {
  name = "Default";
  posX1 = 0.6;
  posY1 = 0.3;
  posX2 = 0.5;
  posY2 = 0.8;
}

Player::Player(std::string name) {
  this->name = name;
  score = 0;
}

string Player::getName() {
  return name;
}

int Player::getScore() {
  return score;
}



void Player::setName(string name) {
  this->name = name;
}

void Player::setScore(int score) {
  this->score = score;
}