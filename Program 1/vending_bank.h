#ifndef VENDING_BANK_H_
#define VENDING_BANK_H_
#include <string>

class VendingBank {
public:
    // Constructors
    VendingBank();
    VendingBank(int id);
    VendingBank(int id, int pennies, int nickels, int dimes, int quarters);

    //getters-setters
    int id() const;
    int coin() const;
    bool setId(int id);
    bool setQuarters(int n);
    bool setDimes(int n);
    bool setNickels(int n);
    bool setPennies(int n);

    // Buy Function
    bool buy(double price, int quantity); //allow customer to buy snacks; return true and reduce balance if enough balance, else return false
    
    // addBal Function
    void addBal(int pennies, int nickels, int dimes, int quarters); //add coins to the vending machine

    // getBal Function
    double getBal() const; //return current balance

    // refund Function
    void refund(); //refund the balance by canceling the transaction

    // Overloaad Operators
    bool operator==(const VendingBank &other) const;

private:
    // id_ is a unique identifier for the VendingBank
    // much like a serial number
    int id_;
    // Different types of coins
    int pennies_;
    int nickels_;
    int dimes_;
    int quarters_;
    double balance_; //current balance of the customer
    double revenue_; //revenue of the vending machine
};

#endif