#include "game.h"
#include <iostream>


Game::Game() {
  player1 = 1;
  player2 = 2;
  gameOver = false;
}

bool Game::mainLoop() {
  while(!gameOver) {
    std::cout << "Inside main loop";
    gameOver = true;
  }
  return gameOver;
}

int Game::getPlayer1() {
  return player1;
}

int Game::getPlayer2() {
  return player2;
}

int Game::getGameOver() {
  return gameOver;
}

void Game::setPlayer1(int p1) {
  player1 = p1;
}

void Game::setPlayer2(int p2) {
  player2 = p2;
}

void Game::setGameOver(bool status) {
  gameOver = status;
}
