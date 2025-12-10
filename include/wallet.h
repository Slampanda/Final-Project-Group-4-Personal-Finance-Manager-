#pragma once
#include <string>

struct Wallet{
    int ID;
    string name; //"Ăn uống", "Tiền nhà", "Du lịch"
    double balance;
};

Wallet createWallet();
void updateWalletBalance(Wallet& w, double amount, bool isIncome);
