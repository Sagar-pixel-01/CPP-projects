

#include<iostream>
#include<string>

class Vehicle{
    protected:
        std::string name;
        float price;
    public:
        virtual void prepareParts() = 0;
        virtual void combineParts() = 0;
        virtual void assembleParts() = 0;
        virtual void attachLable() = 0;
        virtual void showProduct() = 0;

};

class bike: public Vehicle{
     void prepareParts() override{
        std::cout<<"Preparing Bike parts\n";
     }
     void combineParts() override{
        std::cout<<"Combining Bike parts\n";
     }
     void assembleParts() override{
        std::cout<<"Assembling Bike parts\n";
     }
     void attachLable(){
        std::cout<<"Attaching lable to bike\n";
        name = "Bike";
        price = 20;
     }

     void showProduct() override{
        std::cout<<"Showing bike with name "<<name<<" and price "<<price<<"\n";
     }
};



class car: public Vehicle{
     void prepareParts() override{
        std::cout<<"Preparing car parts\n";
     }
     void combineParts() override{
        std::cout<<"Combining car parts\n";
     }
     void assembleParts() override{
        std::cout<<"Assembling car parts\n";
     }
    void attachLable(){
        std::cout<<"Attaching lable to car\n";
        name = "Car";
        price = 30;
     }
    
     void showProduct() override{
        std::cout<<"Showing car with name "<<name<<" and price "<<price<<"\n";
     }
};



class plane: public Vehicle{
     void prepareParts() override{
        std::cout<<"Preparing plane parts\n";
     }
     void combineParts() override{
        std::cout<<"Combining plane parts\n";
     }
     void assembleParts() override{
        std::cout<<"Assembling plane parts\n";
     }
     void attachLable(){
        std::cout<<"Attaching lable to plane\n";
        name = "Plane";
        price = 40;
     }
      
     void showProduct() override{
        std::cout<<"Showing plane with name "<<name<<" and price "<<price<<"\n";
     }
};