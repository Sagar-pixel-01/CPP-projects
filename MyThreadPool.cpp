      
#include <bits/stdc++.h>
using namespace std;


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

string get_thread_id(){
 auto myid = this_thread::get_id();
 stringstream ss;
 ss << myid;
 return ss.str();

}

int main(){
    ThreadPool tp(8);

    for(int i=0;i<40;i++){
        tp.enqueue([i]{
            printf("Enqueued task %d by thread id: %s\n",i,get_thread_id().c_str());
            this_thread::sleep_for(std::chrono::seconds(1)); // Simulate some work
        });
    }
    return 0;
}