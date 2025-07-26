// tic_tac_toe.hpp
#pragma once
#include <vector>
#include <memory>
#include <utility>
#include <string>
#include <iostream>
class Board{
    private:
        const int size;
        std::vector<std::vector<char>> cells;
    public:
        Board(int _size): size(_size){
            cells.resize(size,std::vector<char>(size,'\0'));
        }
        void makeMove(std::pair<int,int> i, char C);
        bool isFull() const;
        bool isWin() const;
        void display() const;
        void reset();
        int getSize() const;

};


class Player{
    protected:
        char symbol;
        std::string name;
    
    public:
        Player(char _symbol, std::string _name): symbol(_symbol),name(_name){}
        virtual ~Player(){
            std::cout<<getname()<<" calling Destroyed\n";
        }
        virtual std::pair<int,int> nextMove(const Board&) = 0;
        char getSymbol(){ return symbol;}
        std::string getname() {return name;}
};


class HumanPlayer: public Player{
    public:
        HumanPlayer(char symbol, std::string name): Player(symbol,name){};
        std::pair<int,int> nextMove(const Board& board) override;
};


class RandomAIPlayer: public Player{
    public:
        RandomAIPlayer(char symbol, std::string name): Player(symbol,name){};
        std::pair<int,int> nextMove(const Board& board) override;
};

class GameController{
    private:
        Board board;
        std:: unique_ptr<Player> player1;
        std:: unique_ptr<Player> player2;
        Player* currentPlayer;
    public:
        GameController(std::unique_ptr<Player> p1,std::unique_ptr<Player> p2,
        int boardSize):player1(std::move(p1)),player2(std::move(p2)),board(boardSize),currentPlayer(nullptr){}
        void run();

};

