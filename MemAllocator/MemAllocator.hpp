#pragma once

#include <cstddef>
#include <stdexcept>
#include <mutex>
#include <iostream>
#include <cstring> // for memcpy


    struct  BlockHeader
        {
        size_t size;
        bool isFree;
        BlockHeader* next;
        } ;

constexpr size_t minSplitSize = 8;

class MemAllocator{
    private:
    
        void* pool_;
        size_t poolSize_;
        BlockHeader* head_;
        std:: mutex mutex_;
    public:
        explicit MemAllocator(size_t size): poolSize_(size){
            if(size<sizeof(BlockHeader) + minSplitSize){
                throw std:: invalid_argument("PoolSize too small");
            }
            pool_ = :: operator new(poolSize_);
            head_ = static_cast<BlockHeader*> (pool_);
            head_->size = poolSize_ - sizeof(BlockHeader);
            head_->isFree = true;
            head_->next = nullptr;
        }
        void* allocate(size_t reqSize){
            std:: lock_guard<std:: mutex> lg(mutex_);
            BlockHeader* best = nullptr;
            BlockHeader* curr = head_;

            while(curr){
                if(curr->isFree && curr->size>=reqSize){
                    if(!best || curr->size<best->size){
                        best=curr;
                    }
                }
                curr= curr->next;
            }

            if(!best) throw std::bad_alloc();

            if(best->size>=reqSize + sizeof(BlockHeader)+minSplitSize){
                char* newCharBlock = reinterpret_cast<char*> (best) + sizeof(BlockHeader) + reqSize;
                BlockHeader* newBlock = reinterpret_cast<BlockHeader*> (newCharBlock);
                newBlock->isFree = true;
                newBlock->size =  best->size - reqSize - sizeof(BlockHeader);
                newBlock->next = best->next;
                best->size = reqSize;
                best->next = newBlock;

            }
            

            best->isFree = false;
            return reinterpret_cast<char*>(best) + sizeof(BlockHeader);
        }


        void deallocate(void* ptr){
            if(!ptr) return ;
            if (ptr < pool_ || ptr >= static_cast<char*>(pool_) + poolSize_)
              return; //
            std:: lock_guard<std:: mutex> lg(mutex_);
            auto* block =  reinterpret_cast<BlockHeader*> (reinterpret_cast<char*>(ptr) - sizeof(BlockHeader));
            block->isFree = true;
        }

        void defragment(){

            BlockHeader* curr = head_;
            std:: lock_guard<std:: mutex> lg(mutex_);
            while(curr && curr->next){
                if(curr->isFree && curr->next->isFree){
                    
                    curr->size +=curr->next->size+sizeof(BlockHeader);
                    curr->next=curr->next->next;
                }
                else{
                    curr=curr->next;
                }
            }
        }
        
    void debugPrint() {
        std:: lock_guard<std:: mutex> lg(mutex_);
        BlockHeader* curr = head_;
        int index = 0;
        while (curr) {
            std::cout<< "Block "<<index++
                 <<" | size: "<<curr->size
                 <<" | isFree: "<<std::boolalpha<<curr->isFree
                 <<"\n";
            curr = curr->next;
        }
    }
    ~MemAllocator(){
        ::operator delete(pool_);
    }
        

};

