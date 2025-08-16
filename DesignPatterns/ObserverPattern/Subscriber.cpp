#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <set>
class Channel;

class Subscriber{
    public:
        virtual void notify( Channel* Channel,const std::string& title)=0;
        virtual ~Subscriber() = default;
};


class Channel{

    private:
        std:: string name;
        std::vector<Subscriber*> subscribers;
    public:
        Channel(const std::string& _name):name(_name){};

        void upload(const std:: string& title){
            std::cout<<"Uploading a video with title "<<title<<std::endl;
            notify(title);
        }
        void notify(const std:: string& title){

            for(auto sub: subscribers){
                sub->notify(this,title);
            }
        }
        void attach(Subscriber* subscriber){
            subscribers.push_back(subscriber);
        }
        void dettach(Subscriber* subscriber){
             subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), subscriber), subscribers.end());
        }
        std:: string getName() const{
            return name;
        }



};

class User:public Subscriber{
    private: 
        std:: string name;
        std::set<Channel*> channels; 
    public:
        User(const std:: string& _name):name(_name){}
        void subscribe(Channel* ch){
            auto it = channels.find(ch);
            if(it==channels.end()){
                channels.insert(ch);
                ch->attach(this);
            }
           
        }

        void unsubscribe(Channel* ch){
           auto it= channels.find(ch);
           if(it!=channels.end()){
                (*it)->dettach(this);
                channels.erase(it);
           }
            
        }

        void notify( Channel* channel, const std::string& title) override{
           std:: cout<<"Notifying User "<<name<<std::endl;
           std::cout<<"Channel "<<channel->getName()<<" posted a new video with title "<<title<<std::endl;
        }

};


int main(){
    Channel* channel= new Channel("KidsTV");
    User user1("Sagar");
    User user2("Sapna");
    user1.subscribe(channel);
    user2.subscribe(channel);
    channel->upload("New Doareamon Episode");
    user1.unsubscribe(channel);
    channel->upload("New Shinchan Episode");
    delete channel;

    

}