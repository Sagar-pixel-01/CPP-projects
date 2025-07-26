
#include "Bank.hpp"
#include "Account.hpp"
#include <string>
#include <unordered_map>
#include <iostream>
//    void addAccount(std:: unique_ptr<Account> account);
//         Account* getAccount(std::string accountNumber);


void Bank:: addAccount(int accountNumber, const std::string& pin, double initialBalance){
    accounts[accountNumber] = std:: make_unique<Account> (accountNumber,pin,initialBalance);
}

Account*  Bank:: getAccount(int accountNumber){
    auto it = accounts.find(accountNumber);
    if(it!=accounts.end()){
        return it->second.get();
    }
    std::cout<<"Account not found\n";
    return nullptr;

}