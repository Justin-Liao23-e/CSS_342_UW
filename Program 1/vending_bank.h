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

    // Coin management functions
    void insertCoin(double amount); // Adds the inserted coin to the balance
    double currentBalance() const;  // Returns the current balance
    double refundCoins();           // Refunds all inserted coins, returning the balance to 0

    // Snack purchase functions
    bool purchaseSnack(double price);  // Attempts to purchase a snack, returns true if successful, false if insufficient funds

    // Reset the bank
    void resetBank();  // Resets the bank to its initial state, clearing the balance

private:
    // id_ is a unique identifier for the VendingBank
    // much like a serial number
    int id_;
    double balance_; //current balance of the customer
    double revenue_; //revenue of the vending machine
};

#endif