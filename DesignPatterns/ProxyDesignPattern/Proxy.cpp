#include<iostream>
#include<memory>
#include<unordered_set>
#include<string>


class DataBase{
    public:
    virtual void query(const std:: string& sql) const =0;
    virtual ~DataBase()=default;
};

class RealDataBase: public DataBase{
    public:
    void query(const std:: string& sql) const override{
        std:: cout<<"Excecuting query: "<<sql<<std::endl;
    }
    
};

class DataBaseProxy{
    private:
        std::unordered_set<std::string> _allowedUsers;
        DataBase* dataBase;
    public:
        DataBaseProxy(DataBase*  _database): dataBase(_database){}
        void registerUser(const std:: string& user){

            auto it = _allowedUsers.find(user);

            if(it==_allowedUsers.end()){
                    _allowedUsers.insert(user);
            }

        }

        void removeUser(const std:: string& user){
             auto it = _allowedUsers.find(user);

            if(it !=_allowedUsers.end()){
                    _allowedUsers.erase(it);
            }
        }

        void query(const std::string& user,const std::string& sql){
            if(isValidUser(user)){
                std:: cout <<"Executing query for User: "<<user<<std::endl;
                dataBase->query(sql);
            }
            else{
                std:: cout<<"Invalid User: "<<user<<std::endl;
            }
        }

        bool isValidUser(const std:: string& user){
            return _allowedUsers.find(user)!=_allowedUsers.end();
        }

};

int main(){
    std:: shared_ptr<DataBase> dataBase = std:: make_shared<RealDataBase>();
    DataBaseProxy dataBaseProxy(dataBase.get());
    std:: string user1="User";
    std:: string user2="Admin";

    dataBaseProxy.registerUser(user1);
    dataBaseProxy.registerUser(user2);
    dataBaseProxy.query(user1,"SELECT * FROM employees");
    dataBaseProxy.query(user2,"INSERT INTO employees VALUES('John', 'Doe', '30')");
    dataBaseProxy.removeUser(user2);
    dataBaseProxy.query(user2,"SELECT * FROM employees");

}