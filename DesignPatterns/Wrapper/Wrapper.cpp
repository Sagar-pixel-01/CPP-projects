#include <iostream>
#include <vector>

template <typename T>

class VectorWrapper{
    private:
        std:: vector<T> vec;
    public:

        void addElement(const T& element){
            vec.push_back(element);
        }
        
        void removeBack(){
            vec.pop_back();
        }
        
        size_t getSize(){
            return vec.size();
        }

        void print(){
            for(const auto& el: vec){
                std::cout<<el<<" ";
            }
            std::cout<<std::endl;
        }
};


int main(){
    VectorWrapper<int> vec;
    vec.addElement(1);
    vec.addElement(4);
    vec.addElement(5);
    vec.addElement(6);
    std::cout<< vec.getSize()<<std:: endl;
    vec.print();
    vec.removeBack();
    vec.print();


}