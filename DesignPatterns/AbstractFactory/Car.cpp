#include <iostream>

class Tire{
    protected:
        int _pressure;
    public:

        Tire(int pressure=0):_pressure(pressure){}

        int getPressure(){
            return _pressure;
        }
};


class Body{
    protected:
        int _strength;
    public:

        Body(int strength=0):_strength(strength){}

        int getStrength(){
            return _strength;
        }
};


class RegularTire:public Tire{
    public:
        RegularTire():Tire(40){}
};

class LuxuryTire:public Tire{
    public:
        LuxuryTire():Tire(100){}
};


class RegularBody:public Body{
    public:
        RegularBody():Body(60){}
};

class LuxuryBody:public Body{
    public:
        LuxuryBody():Body(120){}
};


class Car{
    protected: 
        std:: string _name; 
        Tire* _tire;
        Body* _body;
    public:

        Car(std:: string name): _name(name),_tire(nullptr),_body(nullptr){}

        void setTire(Tire* tire){
                _tire = tire;

        }

        void setBody(Body* body){
            _body = body;
        }

        void showCar(){
            std:: cout<<"Regular Car " <<_name<< " Tire pressure "<<_tire->getPressure()
            <<" and body strength "<<_body->getStrength()<<std::endl;
        }

};


