
#include <iostream>

template<typename T>

class UniquePtr{
    private:
        T* ptr;
    public:
        UniquePtr(T* _ptr = nullptr):ptr(_ptr){}
        ~UniquePtr(){
            delete ptr;
            ptr=nullptr;
        }
        UniquePtr(const UniquePtr& otherPtr) = delete;
        UniquePtr& operator = (const UniquePtr& otherPtr) = delete;

        UniquePtr (UniquePtr&& otherPtr):ptr(otherPtr.ptr){
            otherPtr.ptr=nullptr;
        }
        UniquePtr& operator = (UniquePtr&& otherPtr){
            if(this != &otherPtr){
                    delete ptr;
                    ptr=otherPtr.ptr;
                    otherPtr = nullptr;
            }
            return *this;

        }


        T*  get(){
            return ptr;
        }

        void reset(T* newPtr=nullptr){
            delete ptr;
            ptr=newPtr;
        }

        T& operator *() {
            return *ptr;
        }

        T* operator ->(){
            return ptr;
        }

        T* release(){
            T* temp = ptr;
            ptr=nullptr;
            return temp;
        }


};



int main(){
    UniquePtr<int> p1(new int(42));
    UniquePtr<int> p2 = std::move(p1);
    std::cout << *p2 << "\n";  // 42    
}