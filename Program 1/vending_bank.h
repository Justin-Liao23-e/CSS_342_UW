#ifndef VENDING_BANK_H_
#define VENDING_BANK_H_
#include <string>

class VendingBank {
public:
    // Constructors
    VendingBank();
    VendingBank(int id);

    //getters-setters
    int id() const;
    void setId(int id);

    // Buy Function
    bool buy(double price, int quantity); //allow customer to buy snacks; return true and reduce balance if enough balance, else return false

    // addBal Function
    void addBal(double amount); //add amount to the balance

    // getBal Function
    double getBal() const; //return current balance

    // refund Function
    void refund(); //refund the balance by canceling the transaction

private:
    // id_ is a unique identifier for the VendingBank
    // much like a serial number
    int id_;
    double balance_; //current balance of the customer
    double revenue_; //revenue of the vending machine
};

#endif