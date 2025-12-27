#pragma once
#include "wallet.h"
#include "dynamicArray.h"

class WalletManager{
private:
    DynamicArray<Wallet> wallets;
    int nextWalletID = 1;
    std::string namePoolFile;
    
    long long calculateNameOffset() const;
    
public:
    WalletManager(const std::string& nameFile = "data/walletNames.bin");
    
    int addWallet(const std::string& name, double initialBalance = 0.0);
    
    std::string getWalletNameFromId(int id) const;
    double getWalletBalance(int id) const;
    const Wallet& getWalletByIndex(int index) const;
    
    void updateWalletBalance(int id, double amount, bool isIncome);
    void renameWallet(int id, const std::string& newName);
    
    void showWallets() const;
    
    int getSize() const;
    double getTotalBalance() const;
    
    void save(const std::string& filename) const;
    void load(const std::string& filename);
    
    void rebuildAndSaveNamePool();
};
