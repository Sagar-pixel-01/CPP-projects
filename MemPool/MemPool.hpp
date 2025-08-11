#pragma once

#include <mutex>
#include <memory>
#include <vector>
#include <stdexcept>

class MemoryPool{
    private:
        void*  pool_;
        size_t blockSize_;
        size_t blockCount_;
        std::  vector<void*> freelist_;
        std::  mutex mutex_;
    public:
        explicit MemoryPool (size_t blockSize,size_t blockCount):
        blockSize_(blockSize),blockCount_(blockCount){  
               
                pool_ = ::operator new(blockCount_ * blockSize_);
                freelist_.reserve(blockCount_);

            // Populate freeList
            for(size_t i=0;i<blockCount_;++i){
                void* block = static_cast<char*> (pool_) + i*blockSize_;
                freelist_.push_back(block);
            }

        }

        void* allocate(){
            std:: lock_guard<std::mutex> lg(mutex_);
            if(freelist_.empty()){
                throw std::bad_alloc();
            }
            void* ptr = freelist_.back();
            freelist_.pop_back();
            return ptr;
        }

        void deallocate(void* ptr){
            std:: lock_guard<std::mutex> lg(mutex_);
            freelist_.push_back(ptr);
        }

        ~MemoryPool(){
            ::operator delete(pool_);
        }
};