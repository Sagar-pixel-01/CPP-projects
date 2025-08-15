#include<iostream>
#include"VehicleFactory.cpp"


int main(){
     int a;
    while(1){
            std::cout<<"Enter vehichle type or zero for exit ";
           
            std::cin>>a;

            if(!a) break;

            Vehicle* vehicle = VehicleFactory::makeVehicle(a);
            if(vehicle){
                vehicle->showProduct();
                delete vehicle;
            }

    }
    std::cout<<"Exiting...\n";
}