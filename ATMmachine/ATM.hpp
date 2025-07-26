#pragma once
#include "Bank.hpp"
#include <vector>



class ATM{
    private:
        Bank& bank;
        Account* currAccount;

        void login();
        void showMenu();
        void handleInput(int choice);
    public:
        ATM(Bank& _bank): bank(_bank),currAccount(nullptr){}
        void start();

};