#define PLAYER_H Player player;

class Game{
  private:
    int player1;
    int player2;
    bool gameOver;
  public:
    Game();
    bool mainLoop();

    int getPlayer1();
    int getPlayer2();
    int getGameOver();

    void setPlayer1(int p1);
    void setPlayer2(int p2);

    void setGameOver(bool status);

};