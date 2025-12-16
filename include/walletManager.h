#pragma once
#include "Wallet.h"
#include "dynamicArray.h"

class ManagerWallet {
private:
    DynamicArray<Wallet> wallets;
    int nextWalletID = 1;
public:
    ManagerWallet();
    int addWallet (const std::string &name);
    std::string getWalletNameFromId(int id) const;
    void showWallets() const;
    void save(const std::string& filename) const;
    void load(const std::string& filename);
};