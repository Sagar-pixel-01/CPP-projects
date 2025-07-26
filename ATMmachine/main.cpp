#include "ATM.hpp"
#include "Bank.hpp"
#include "Account.hpp"
#include <iostream>
int main(){

    Bank bank;

    // Adding sample accounts
    bank.addAccount(1, "123", 1000.0);
    bank.addAccount(2, "456", 500.0);
    bank.addAccount(3, "789", 250.0);

    ATM atm(bank);  // ✅ Pass by reference
    atm.start();    // 🔁 Begin ATM loop

    return 0;  
}