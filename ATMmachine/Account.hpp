#pragma once
#include <string>


class Account{
    private:
         int accountNumber;
        std:: string pin;
        double balance;
    public:
        Account(int _accountNumber,std::string _pin,double _balance): accountNumber(_accountNumber)
        ,pin(_pin),balance(_balance){}

        bool authenticate(const std:: string& enteredpin) const;

        double getBalance() const;

        bool deposit(double val);
        
        bool withdraw(double val);

        int getAccountNumber() const;

};


