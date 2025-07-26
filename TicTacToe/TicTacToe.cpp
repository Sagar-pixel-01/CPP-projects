#include "TicTacToe.hpp"
#include <memory>
#include <utility>
#include <iostream>

void Board:: makeMove(std::pair<int,int>i, char symbol){
    int r= i.first;
    int c = i.second;
    if(r>=size || c>=size) {
        throw std::invalid_argument("Invalid argument");
    }
    if(cells[r][c]!='\0'){
        throw std::invalid_argument("Cell already filled");
    }
    cells[r][c]=symbol;
}

bool Board:: isFull() const{
    for(const auto& row: cells){
        for(const auto& cell: row){
            if(cell=='\0') return false;
        }
    }
    return true;
}

bool Board:: isWin() const{
   // check rows
    for(size_t r=0;r<size;r++){
        if(cells[r][0]=='\0') continue;
        bool is_same = true;
        for(size_t c=1;c<size;c++){
            if(cells[r][c]!=cells[r][c-1]) {
                is_same = false;
                break;
            }
        }
        if(is_same) return true;
    }

    // check columns
    for(size_t c=0;c<size;c++){
         if(cells[0][c]=='\0') continue;
        bool is_same = true;
        for(size_t r=1;r<size;r++){
            if(cells[r][c]!=cells[r-1][c]) {
                is_same = false;
                break;
            }
        }
        if(is_same) return true;
    }

    // check diagonal 1
   
    if(cells[0][0]!='\0'){
        bool is_same = true;
        for(size_t d=1;d<size;d++){
            if(cells[d][d]!=cells[d-1][d-1]) {
                is_same = false;
                break;
            }
        }
        if(is_same) return true;
    }
    

    // check diagoanal 2
    if(cells[0][size-1]!='\0'){
        bool is_same = true;
        for(size_t d=1;d<size;d++){
            if(cells[d][size-d-1]!=cells[d-1][size-d]) {
                is_same = false;
                break;
            }
        }
        if(is_same) return true;
    }

    return false;
}  


void Board:: display() const{
    for(const auto& row: cells){
        for(const auto& cell: row){
            if(cell=='\0'){
                std::cout<<"."<<" ";
            }
            else
                std::cout<<cell<<" ";
        }
        std::cout<<"\n";
    }
}

void Board:: reset() {
 for( auto& row: cells){
    std::fill(row.begin(),row.end(),'\0');
 }
}

int Board:: getSize() const{
    return size;
}


// HumanPlayer next move



std:: pair<int,int> HumanPlayer:: nextMove(const Board& board){
    int row , column;
    std:: cout<< getname() << " ( "<<getSymbol()<< " ) "<<"Please enter row and column for your next move\n";
    std::cin>>row>>column;

    return std:: make_pair(row,column);

}
std:: pair<int,int> RandomAIPlayer:: nextMove(const Board& board){
    std:: cout<< getname()<<" ( " << getSymbol()<< " ) "<<" making move"<<std::endl;
    int size = board.getSize();
    int row = rand()%size;
    int column = rand()%size;
    return std::make_pair(row,column);
}


// Game controller implementation

void GameController:: run(){
    currentPlayer = player1.get();
    
    while(true){
        board.display();
        auto move = currentPlayer->nextMove(board);
        try{
            board.makeMove(move,currentPlayer->getSymbol());
        }
        catch (const std:: exception& e){
            std::cout<< e.what()<<"\n";
            continue;
        }
        if(board.isWin()){
            std:: cout<<"Winner of the Game is "<<currentPlayer->getname()<<std::endl;
            break;
        }
        if(board.isFull()){
            std:: cout<<"WGame is drawn, please restart the game\n"<<std::endl;
            break;
        }

        currentPlayer = (currentPlayer==player1.get())? player2.get():player1.get();
    }
}   