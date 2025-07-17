#include <bits/stdc++.h>
using namespace std;


class Object{
    private:
        int id;
    public:
        Object(){
            id =0;
            cout<<"Created Object with 0"<<endl;
        }
        Object(int _id): id(_id){
            cout<<"Created Object with id: "<<id<<endl;
        }
        void doSomething(){
            cout<<"Object doing some work"<<endl;
        }
};

class ObjectPool{
    private:
        vector<shared_ptr<Object>> objects;
        int maxSize;
    public:
        ObjectPool(int size): maxSize(size){
            for(int i=0;i<maxSize;i++){
                objects.emplace_back(make_shared<Object>(i));
            }
        }
        shared_ptr<Object> acquireObject(){
            if(!objects.empty()){
                cout<<"Acquiring object from objectpool"<<endl;
                auto obj = objects.back();
                objects.pop_back();
                return obj;
            }
            else{
                cout<<"Objectpool empty, returning new Object"<<endl;
                return make_shared<Object>();
            }
        }
        void releaseObject(shared_ptr<Object> A){
            if(objects.size()<maxSize){
                cout<<"Returning object to Objectpool"<<endl;
                objects.emplace_back(move(A));
            }
            else{
                cout<<"ObjectPool is full, object will be destroyed"<<endl;
            }
        }
};


int main(){
    ObjectPool objpool(3);
    auto obj1 =  objpool.acquireObject();
    auto obj2 =  objpool.acquireObject();
    auto obj3 =  objpool.acquireObject();

    obj1->doSomething();
    obj2->doSomething();
    obj3->doSomething();

    auto obj4 = objpool.acquireObject();

    obj4->doSomething();

    objpool.releaseObject(obj1);
    objpool.releaseObject(obj2);
    objpool.releaseObject(obj3);


    objpool.releaseObject(obj4);    
    
}
