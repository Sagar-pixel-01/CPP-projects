#include <iostream>

#include "Car.cpp"


class CarFactory{
    protected:
        virtual Tire* buildTire()=0;
        virtual Body* buildBody()=0;
    public:
     virtual Car* makeCar()=0;
};


class LuxuryCarFactory: public CarFactory{
    protected:
        Tire* buildTire() override{
            return new LuxuryTire();
        }

        Body* buildBody() override{
            return new LuxuryBody();
        }
    public:
        Car* makeCar(){
            Car* car = new Car("Mercedes Benz");
            car->setTire(buildTire());
            car->setBody(buildBody());
            return car;
        }

};


class RegularCarFactory: public CarFactory{
    protected:
        Tire* buildTire() override{
            return new RegularTire();
        }

        Body* buildBody() override{
            return new RegularBody();
        }
    public:
        Car* makeCar(){
            Car* car = new Car("Maruti suzuki");
            car->setTire(buildTire());
            car->setBody(buildBody());
            return car;
        }

};