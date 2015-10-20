#include <iostream>
#include <string>

class Player {

  private:
    //we may not even need posX
    //for pong
    float posX; 
    float posY;
    std::string name;
    int score;

  public:
    Player();
    Player(std::string name);

    float        getPosY();
    std::string  getName();
    int          getScore();

    void setPosY(int posY);
    void setName(std::string name);
    void setScore(int score);
};