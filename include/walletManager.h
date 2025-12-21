#pragma once
#include "wallet.h"
#include "dynamicArray.h"

class ManagerWallet{
private:
    DynamicArray<Wallet> wallets;
    int nextWalletID = 1;
    std::string namePoolFile;
    
    long long addToNamePool(const std::string& name);
    
public:
    ManagerWallet(const std::string& nameFile = "Users/macair/Downloads/PersonalFinanceManager/PersonalFinanceManager/data/walletNames.bin");
    int addWallet(const std::string &name, double initialBalance = 0.0);
    std::string getWalletNameFromId(int id) const;
    double getWalletBalance(int id) const;
    void updateWalletBalance(int id, double amount, bool isIncome);
    void showWallets() const;
    int getSize() const;
    double getTotalBalance() const;
    const Wallet& getWalletByIndex(int index) const;
    void save(const std::string& filename) const;
    void load(const std::string& filename);
};
