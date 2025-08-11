#include <iostream>
#include <string>
class Trade{
    private:
        int id;
        double price;
        std:: string symbol;
    public:
       explicit Trade(int _id, double _price, std::string _symbol): 
       id(_id),price(_price),symbol(_symbol){

        std::cout<<"Trade constructed: "<<symbol<<" @ "<<price<<std::endl;

       }
       ~Trade(){
        std::cout<<"Trade destructed: "<<symbol<<std::endl;
       }

};