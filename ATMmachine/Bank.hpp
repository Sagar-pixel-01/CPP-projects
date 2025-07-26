#pragma once
#include "Account.hpp"
#include <memory>
#include <unordered_map>
#include <string>
class Bank{
    private:
        std:: unordered_map<int,std::unique_ptr<Account>> accounts;
    public:
        void addAccount(int accountNumber,const std:: string& pin, double initialBalance);
        Account* getAccount(int accountNumber);

};