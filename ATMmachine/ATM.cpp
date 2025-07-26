
    #include "ATM.hpp"
       
    #include <string> 
    #include <memory>
    #include <iostream>
       

    void  ATM:: start(){
        login();
        while(currAccount){
            showMenu();
            int choice;
            std::cin>>choice;
            handleInput(choice);
        }
    }

    void ATM :: login(){
        int accountNumber;
        std:: string pin;
        std:: cout<<"Enter account number: ";
        std:: cin>>accountNumber;
        std:: cout<<"Enter account pin: ";
        std:: cin>>pin;
        currAccount = bank.getAccount(accountNumber);

        if(currAccount){
           bool authenticated = currAccount->authenticate(pin);
           if(!authenticated){
                currAccount = nullptr;
                std:: cout << "Authentication failed\n";
                return;
           }
           std:: cout<<"Authentication succesfull\n";
        }

    }

    void ATM:: showMenu(){
        std:: cout<<"\n----ATM Menu----\n";
        std:: cout <<" 1: Check balance\n";
        std:: cout <<" 2: Deposit amount\n";
        std:: cout <<" 3: Withdraw amount\n";
        std:: cout << "4: Exit.\n";
        std:: cout << "Choose an option: ";
    }

    void ATM:: handleInput(int choice){
        double amount;
        switch (choice){
            case 1:
                std:: cout << "Current balance is "<<currAccount->getBalance()<<std::endl;
                break;
            case 2:
                std:: cout<<"Enter amount to deposit:  ";
                std:: cin>>amount;
                if(currAccount->deposit(amount)){
                     std:: cout<<"Deposit succesfull\n";
                }
                else{
                     std:: cout<<"Deposit Failed";
                }
                break;
            case 3:
                std:: cout<<"Enter amount to withdraw:  ";
                std:: cin>>amount;
                if(currAccount->withdraw(amount)){
                     std:: cout<<"Withdraw succesfull\n";
                }
                else{
                     std:: cout<<"Withdraw Failed";
                }
                break;
                
            case 4:
                currAccount=nullptr;
                std:: cout <<"Exiting the ATM\n";
                std:: cout<<"Thankyou\n";
                break;
            default:
                std:: cout<<"Invalid choice\n";
                break;

        }
    }