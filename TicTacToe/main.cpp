#include "TicTacToe.hpp"
#include <memory>

int main(){
    std:: unique_ptr<Player> player1 = std:: make_unique<HumanPlayer> ('O',"Sagar");
    std:: unique_ptr<Player> player2 = std:: make_unique<RandomAIPlayer> ('X',"prashantAI");
    GameController gameController (std:: move(player1),std:: move(player2),3);
    gameController.run();

}