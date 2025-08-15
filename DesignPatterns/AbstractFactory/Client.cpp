#include <iostream>
#include "CarFactory.cpp"

#define REGULAR 1
#define LUXURY 1

int main(){

   

    #ifdef REGULAR
        CarFactory* carFactory= new RegularCarFactory();
       

    #elif LUXURY
       CarFactory* carFactory= new LuxuryCarFactory();
      

    #endif

    Car* car = carFactory->makeCar();
    car->showCar();
    delete car;
    delete carFactory;
    car=nullptr;
    carFactory=nullptr;

}