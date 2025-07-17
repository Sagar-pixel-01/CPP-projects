#include <bits/stdc++.h>
using namespace std;
string get_thread_id();
class Object{
    public:
        int num;
        Object(int _num):num(_num){
            printf("Created obj with id  %d\n",num);
        }
        void doSomething(int w){
            printf("Object %d doing something\n",num);
            this_thread::sleep_for(chrono::milliseconds(w));
        }
};

class ObjectPool{
    private:
        mutex queueMutex;
        queue<shared_ptr<Object>> queue;
        int numObj;
        
    public:
        ObjectPool(int _numObj): numObj(_numObj){
             for(int i=0;i<numObj;++i){
                queue.push(make_shared<Object>(i));
             }
        }
        shared_ptr<Object> acquireObject(){
            unique_lock<mutex> ul(queueMutex);
            if(queue.empty()) return nullptr;
            auto obj = move(queue.front());
            queue.pop();
            printf("Object acquired by thread %s\n",get_thread_id().c_str());
            return obj;
        }
        void releaseObject(shared_ptr<Object> obj){
            if(obj){
                printf("Releasing obj with id %d\n",obj->num);
                unique_lock<mutex> ul(queueMutex);
                queue.push(move(obj));
            }
        }
};

string get_thread_id(){
    stringstream ss;
    ss << this_thread::get_id();
    return ss.str();
}

void worker(ObjectPool &pool){
    for(int i=0;i<15;i++){
        auto obj = pool.acquireObject();
        if(obj){
            int w = rand()%1000;
           obj->doSomething(w);
           pool.releaseObject(obj);
        }
        else{
            printf("Thread %s failed to acquire object\n",get_thread_id().c_str());
        }
    }
       
}
class ThreadPool{
    private:
        bool stop;
        vector<thread> workers;
        queue <function<void()>> tasks;
        mutex queueMutex;
        condition_variable cv;

    public:
        ThreadPool(int numThread):stop(false){
            for(int i=0;i<numThread;i++){
                workers.emplace_back([this]{
                    for(;;){
                        unique_lock<mutex> ul(queueMutex);
                        cv.wait(ul,[this]{return (stop || !tasks.empty());});
                        if(stop && tasks.empty()) return;
                        auto task = move(tasks.front());
                        tasks.pop();
                        ul.unlock();
                        task();
                    }
                });
            }
        }
        template<class F>
        void enqueue(F&& task){
            unique_lock<mutex> ul(queueMutex);
            tasks.emplace(forward<F>(task));
            ul.unlock();
            cv.notify_one();
        }
        ~ThreadPool(){
            unique_lock<mutex> ul(queueMutex);
            stop = true;
            ul.unlock();
            cv.notify_all();
            for(thread &th: workers){
                th.join();
            }
        }
};

int main(){
    ObjectPool op(3);
    ThreadPool tp(4);
    
    for(int j=0;j<5;j++){
        tp.enqueue([j,&op]{
                printf("Enqueued task %d by thread id: %s\n",j,get_thread_id().c_str());
                for(int i=0;i<15;i++){
                    auto obj = op.acquireObject();
                    if(obj){
                        int w = rand()%1000;
                    obj->doSomething(w);
                    op.releaseObject(obj);
                    }
                    else{
                        printf("Thread %s failed to acquire object\n",get_thread_id().c_str());
                    }
                }
        });
    }

    

}