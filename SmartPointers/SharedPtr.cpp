#include <iostream>

template<typename T>

class SharedPtr{
    private:
        T* ptr;
        int* refCount;
    void release(){
        if(refCount){
            (*refCount)--;
            if(*refCount==0){
                delete ptr;
                delete refCount;
            }
            ptr=nullptr;
            refCount=nullptr;
        }
    }
    public:
        SharedPtr(T* _ptr=nullptr): ptr(_ptr),refCount(nullptr){
           if(ptr) refCount = new int(1);
        }
        ~SharedPtr(){
           release();
            
        }

        SharedPtr(const SharedPtr& otherPtr){
            ptr=otherPtr.ptr;
            refCount = otherPtr.refCount;
            if(ptr){
                 (*refCount)++;
            }
           
        }

        SharedPtr( SharedPtr&& otherPtr){
            ptr=otherPtr.ptr;
            refCount = otherPtr.refCount;
            otherPtr.ptr = nullptr;
            otherPtr.refCount = nullptr;
        }
        
        SharedPtr& operator =(const SharedPtr& otherPtr){
            if(this!= &otherPtr){
                 release();
                 ptr=otherPtr.ptr;
                 refCount = otherPtr.refCount;
                
                if(ptr) (*refCount)++;
            }
            return *this;
        }
        SharedPtr& operator =( SharedPtr&& otherPtr){
            if(this!= &otherPtr){
                release();
                ptr=otherPtr.ptr;
                refCount = otherPtr.refCount;
                otherPtr.ptr = nullptr;
                otherPtr.refCount = nullptr;
                 
            }
            return *this;
        }

        T* get() const{
            return ptr;
        }

        void reset(T* newPtr=nullptr){
            release();
            ptr = newPtr;

           if(ptr) refCount = new int(1);
        }

        T& operator *() {
            return *ptr;
        }

        T* operator ->(){
            return ptr;
        }
        
        int use_count() const{
            return refCount? *refCount:0;
        }
        
};

int main() {
    SharedPtr<int> p1(new int(10));
    std::cout << "Use count after p1: " << p1.use_count() << "\n"; // 1

    SharedPtr<int> p2 = p1;
    std::cout << "Use count after p2 = p1: " << p1.use_count() << "\n"; // 2

    SharedPtr<int> p3;
    p3 = p2;
    std::cout << "Use count after p3 = p2: " << p1.use_count() << "\n"; // 3

    std::cout << "Value: " << *p1 << "\n";  // 10

    p2.reset();
    std::cout << "Use count after p2.reset(): " << p1.use_count() << "\n"; // 2

    p3.reset();
    std::cout << "Use count after p3.reset(): " << p1.use_count() << "\n"; // 1

    p1.reset();
    std::cout << "Use count after p1.reset(): " << p1.use_count() << "\n"; // 0
}