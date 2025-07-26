#include "Account.hpp"
#include <string>

//   bool authenticate(const std:: string& enteredpin) const;

//         double getBalance();

//         void deposit(double val);
        
//         void withdraw(double val);

//         std:: string getAccountNumber() const;


bool Account::authenticate(const std:: string& enteredPin) const{
    return pin==enteredPin;
}

double Account:: getBalance() const{
    return balance;
}

bool Account:: deposit(double val){
    if(val>0){
        balance+=val;
        return true;
    }
    return false;
    
}


bool Account:: withdraw(double val){
    if(val>0 && val<=balance){
        balance-=val;
        return true;
    }
    return false;
    
}

 int Account:: getAccountNumber() const{
    return accountNumber;
}