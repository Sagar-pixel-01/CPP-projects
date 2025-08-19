#include<iostream>
#include<string>


class Plane{
    private:
        std::string name;
        std::string engine;
        std::string body;
    public:
        Plane(const std::string& _name): name(_name){}
        void setEngine(const std:: string &_engine){
            engine = _engine;
            std:: cout<<"Getting "<<engine <<" for "<<name<< " plane\n";
        }

        void setBody(const std:: string &_body){
             body = _body;
             std:: cout<<"Getting "<<body <<" for "<<name<< " plane\n";
        }
        
        std:: string getEngine(){
            return engine;
        }
        std:: string getBody(){
            return body;
        }
        void showPlane(){
            std:: cout<<"Showing plane "<<name
            << " with body: "
            << body << " engine: "<<engine<<std::endl;
        }

};

class PlaneBuilder{
        protected:
            Plane* plane;
        public:
           PlaneBuilder(): plane(nullptr){}
           virtual void buildEngine()=0;
           
           virtual void buildBody()=0;

           virtual void buildAllParts()=0;
           virtual ~PlaneBuilder()= default;
           Plane* getPlane(){
             return plane;
           }

};

class JetBuilder:public PlaneBuilder{
        void buildEngine() override{
            plane->setEngine("Jet Engine");
        }
        void buildBody() override{
            plane->setBody("Jet Body");
        }

        void buildAllParts() override{
            
            plane = new Plane("Jet Plane"); 
        }
        
};

class RegularBuilder:public PlaneBuilder{
        void buildEngine() override{
            plane->setEngine("Regular Engine ");
        }
        void buildBody() override{
            plane->setBody("Regular Body");
        }

        void buildAllParts() override{
            
            plane = new Plane("Regular Plane"); 

        }
        
};

class Director{
    public:
        Plane* directBuildPlane(PlaneBuilder* Builder){
            Builder->buildAllParts();
            Builder->buildEngine();
            Builder->buildBody();
            return Builder->getPlane();
        }

};


int main(){
    JetBuilder jb;
    RegularBuilder rb;
    Director dir;
    Plane* plane1 = dir.directBuildPlane(&jb);
    plane1->showPlane();
    Plane* plane2 = dir.directBuildPlane(&rb);

    plane2->showPlane();
    
}