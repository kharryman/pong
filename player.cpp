#include "player.h"
#include <string>
using namespace std;

Player::Player() {
  name = "Default";
  posY = 0.0;
  score = 0;
}

Player::Player(std::string name) {
  this->name = name;
  posY = 0.0;
  score = 0;
}

float Player::getPosY() {
  return posY;
}

string Player::getName() {
  return name;
}

int Player::getScore() {
  return score;
}

void Player::setPosY(int posY) {
  this->posY = posY;
}

void Player::setName(string name) {
  this->name = name;
}

void Player::setScore(int score) {
  this->score = score;
}