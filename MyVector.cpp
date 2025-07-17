#include <iostream>
#include <stdexcept>

template<typename T>

class MyVector{
    private:
        T* data;
        size_t _size;
        size_t _capacity;
        void resize (size_t new_cap){
            T* newData = new T[new_cap];
            size_t limit = std::min(new_cap,_size);
            for(int i=0;i<limit;i++){
                newData[i]=std::move(data[i]);
            }
            delete[] data;
            data = newData;
            _capacity = new_cap;
            _size = limit;
            

        }

    public:
        MyVector(){
            _size = 0;
            _capacity = 0;
            data = nullptr;
        }
        ~MyVector(){
            delete[] data;
        }

       template <typename U>
        void push_back(U&& val){
            if(_size==_capacity){
                size_t new_capacity = _capacity? 2* _capacity : 1;
                resize(new_capacity);
            }
            data[_size++] = std::forward<U>(val);
        }
        void pop_back(){
            if(_size) _size--;
            else throw std::underflow_error("Myvector is empty");
        }
        size_t size() const{
            return _size;
        }
        size_t capacity() const{
            return _capacity;
        }
        bool empty() const { return _size == 0;}
        void reserve(size_t new_cap){
            if(new_cap>_capacity) resize(new_cap);
        }
        void clear(){
            _size = 0;
        }
        T& operator[] (int index){
            if(index<_size){
                return data[index];
            }
            throw std::out_of_range("Index out of range");
        }
        const T& operator[] (int index) const{
            if(index<_size){
                return data[index];
            }
           throw std::out_of_range("Index out of range");
        }

};

int main(){
    MyVector<int> mv;
    
    for(size_t i=0;i<5;i++){
        mv.push_back(i);
    }
    mv.pop_back();
    for(size_t i =0;i<mv.size();i++){
        std::cout<<mv[i]<<" ";
    }
    std::cout<<"\n";
}