#include "MemAllocator.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <thread>
#include <sstream>
class Trade{
    private:
        int id;
        double price;
        std:: string symbol;
    public:
       explicit Trade(int _id, double _price, std::string _symbol): 
       id(_id),price(_price),symbol(_symbol){

        std::cout<<"Trade constructed: "<<symbol<<" @ "<<price<<std::endl;

       }
       ~Trade(){
        std::cout<<"Trade destructed: "<<symbol<<std::endl;
       }

};


std:: string get_thread_id(){
    auto id = std::this_thread::get_id();
    std:: stringstream ss ;
    ss << id;
    return ss.str();

}
void work(int i, MemAllocator& pool){
    for(int l=0;l<4;l++){
        void* mem = pool.allocate(sizeof(Trade));
        if(mem){
            printf("Trade %d made by thread id: %s\n",i,get_thread_id().c_str());
            Trade* trade = new (mem) Trade(i,100.0+i,"SYM"+std::to_string(i));
            std:: this_thread::sleep_for(std::chrono::seconds(1));
            trade->~Trade();
            pool.deallocate(mem);
        }
        else{
            std:: this_thread::sleep_for(std::chrono::seconds(1));
        }

    }
}
int main() {
    // MemAllocator allocator(1024); // 1 KB

    // void* a = allocator.allocate(100);
    // void* b = allocator.allocate(150);
    // allocator.deallocate(a);
    // allocator.deallocate(b);

    // allocator.debugPrint();
    // allocator.defragment();
    // std::cout << "After defrag:\n";
    // allocator.debugPrint();

    // void* c = allocator.allocate(200); // Should reuse merged block
    // allocator.debugPrint();

 constexpr int poolSize = 4096; // 4 KB memory pool
    MemAllocator allocator(poolSize);

    // constexpr int N = 5;
    // std::vector<void*> allocatedMemory;

    // Allocate and construct N Trade objects

    std::vector<std:: thread> workers;


    for(int i=0;i<4;i++){
        workers.emplace_back([i,&allocator]{
                 for(int l=0;l<4;l++){
                void* mem = allocator.allocate(sizeof(Trade));
                if(mem){
                    printf("Trade %d made by thread id: %s\n",i,get_thread_id().c_str());
                    Trade* trade = new (mem) Trade(i,100.0+i,"SYM"+std::to_string(i));
                    std:: this_thread::sleep_for(std::chrono::seconds(1));
                    trade->~Trade();
                    allocator.deallocate(mem);
                }
                else{
                    std:: this_thread::sleep_for(std::chrono::seconds(1));
                }

        }
        });
    }

    std::cout << "\n--- Debug Print After Deallocation ---\n";
    allocator.debugPrint();

    // Defragment memory pool
    allocator.defragment();

    std::cout << "\n--- Debug Print After Defragmentation ---\n";
    allocator.debugPrint();

    for(int i=0;i<4;i++){
        workers[i].join();
    }
    return 0;

    
}