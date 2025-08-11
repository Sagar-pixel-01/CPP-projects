#include "MemPool.hpp"
#include "Trade.hpp"
#include <vector>
#include <thread>
#include <chrono>

int main(){

    constexpr size_t poolSize = 10;
    
    MemoryPool tradePool(sizeof(Trade),poolSize);

    std:: vector<Trade*> trades;

    for(size_t i=0;i<5;++i){
        void* mem = tradePool.allocate();
        if(mem){
            Trade* t = new (mem) Trade(i,100.0 + i, "AAPL");
            trades.push_back(t);
        }
    }
    std:: this_thread::sleep_for(std::chrono::milliseconds(100));


    for(Trade* t : trades){
        t->~Trade();
        tradePool.deallocate(t);
    }
    return 0;

}