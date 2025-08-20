    #include<iostream>
    #include<unordered_map>
    #include<memory>
    #include<string>

    class Bullet{
        protected:
            std::string _bulletName;
            float _speed;
            float _firePower;
            float _damagePower;
            float _direction;

        public:
            Bullet(const std::string& bulletName,float speed,float firePower,float damagePower):
            _bulletName(bulletName),_speed(speed),_firePower(firePower),_damagePower(damagePower){}
            virtual std::unique_ptr<Bullet> clone()=0;
            virtual ~Bullet()=default;
            void fire(float direction){
                _direction=direction;
                std::cout<<"Firing Bullet "<<_bulletName
                <<" towards "<<_direction
                <<" Speed: "<<_speed<<" firePower: "<<_firePower
                <<" damagePower "<<_damagePower<<'\n';
            }



    };

    class SimpleBullet: public Bullet{
        public:
            SimpleBullet(const std::string& bulletName,float speed,float firePower,float damagePower):Bullet(bulletName,speed,firePower,
                damagePower){}

        std::unique_ptr<Bullet> clone() override{
            return std::make_unique<SimpleBullet>(*this);
        }
    };

    class GoodBullet: public Bullet{
        public:
            GoodBullet(const std::string& bulletName,float speed,float firePower,float damagePower):Bullet(bulletName,speed,firePower,
                damagePower){}

        std::unique_ptr<Bullet> clone() override{
            return std::make_unique<GoodBullet>(*this);
        }
    };

    enum BulletType{
        SIMPLE,
        GOOD
    };


    class BulletFactory{
        private:
           std:: unordered_map<BulletType,std::unique_ptr<Bullet>> mp;
        public:
            BulletFactory(){
                mp[SIMPLE]=std::make_unique<SimpleBullet>("SimpleBullet",5.0,10.0,20.0);
                mp[GOOD]=std::make_unique<GoodBullet>("GoodBullet",10.0,20.0,40.0);
            }
            std::unique_ptr<Bullet> createBullet(BulletType bulletType){
                return mp[bulletType]->clone();
            }

    };


    int main(){
        BulletType BulletType;
        BulletFactory bulletfactory;
        auto bullet = bulletfactory.createBullet(SIMPLE);
        bullet->fire(5.0);
        bullet = bulletfactory.createBullet(GOOD);
        bullet->fire(10.0);


    }