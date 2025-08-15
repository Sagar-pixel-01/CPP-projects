#include<iostream>
#include"Vehicle.cpp"
class VehicleFactory{
    public:
       static  Vehicle* makeVehicle(int v){
            Vehicle* vehicle;
            switch(v){
                case 1:
                    vehicle = new bike();
                    break;
                case 2:
                    vehicle = new car();
                    break;
                case 3:
                    vehicle = new plane();
                    break;
                default:
                    return nullptr;
                    break;
            }
            vehicle->prepareParts();
            vehicle->combineParts();
            vehicle->assembleParts();
            vehicle->attachLable();
            return vehicle;
       }

};