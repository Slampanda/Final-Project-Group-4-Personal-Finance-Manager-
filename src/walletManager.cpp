#include "common.h"
#include "walletManager.h"
#include "numberUtils.h"

ManagerWallet::ManagerWallet(const string& nameFile) : namePoolFile("/Users/macair/Downloads/PersonalFinanceManager/PersonalFinanceManager/data/walletNames.bin"), nextWalletID(1){}

int ManagerWallet::addWallet(const string& name, double initialBalance){
    long long nameOffset = addToNamePool(name);
    size_t nameLen = name.length();
    
    Wallet newWallet(nextWalletID, name, initialBalance, nameLen, nameOffset);
    wallets.add(newWallet);
    return nextWalletID++;
}

long long ManagerWallet::addToNamePool(const string &name){
    ofstream ofs(namePoolFile, ios::binary | ios::app);
    if (!ofs){
        cout << "Cannot open Wallets' name file to save";
        return -1;
    }
    
    long long offset = ofs.tellp();
    ofs.write(name.c_str(), name.length());
    return offset;
}

string ManagerWallet::getWalletNameFromId(int id) const{
    for (int i = 0; i<wallets.getSize(); i++){
        if (wallets[i].getId() == id){
            return wallets[i].getName();
        }
    }
    return "Unknown Wallet";
}

double ManagerWallet::getWalletBalance(int id) const{
    for (int i = 0; i<wallets.getSize(); i++){
        if (wallets[i].getId() == id){
            return wallets[i].getBalance();
        }
    }
    cout << "Unknown Wallet" << endl;
    return 0.0;
}

void ManagerWallet::updateWalletBalance(int id, double amount, bool isIncome){
    for (int i = 0; i<wallets.getSize(); i++) {
        if (wallets[i].getId() == id) {
            double currentBalance = wallets[i].getBalance();
            if (isIncome){currentBalance += amount;}
            else{currentBalance -= amount;}
            wallets[i].setBalance(currentBalance);
            cout << "Updated wallet " << id << " balance: " << formatNumber(currentBalance) << endl;
            return;
        }
    }
    cout << "Wallet ID " << id << " not found!" << endl;
}

void ManagerWallet::showWallets() const {
    cout << "====== WALLET LIST ======" << endl;
    for (int i = 0; i<wallets.getSize(); i++) {
        cout << wallets[i].getId() << " - " << wallets[i].getName() << " - Balance: " << formatNumber(wallets[i].getBalance()) << endl;
    }
}

int ManagerWallet::getSize() const{
    return wallets.getSize();
}

double ManagerWallet::getTotalBalance() const{
    double total = 0;
    for (int i = 0; i<wallets.getSize(); i++){
        total += wallets[i].getBalance();
    }
    return total;
}

const Wallet& ManagerWallet::getWalletByIndex(int index) const{
    if (index < 0 || index >= wallets.getSize()){
        throw out_of_range("Wallet index out of range");
    }
    return wallets[index];
}

void ManagerWallet::save(const string& filename) const{
    ofstream ofs(filename.c_str(), ios::binary);
    if (!ofs){
        cout << "Cannot open Wallet file to save" << endl;
        return;
    }
    // Số lượng wallets
    int walletsCount = wallets.getSize();
    ofs.write((char*)&walletsCount, sizeof(walletsCount));
    
    // ID cho wallet tiếp theo
    ofs.write((char*)&nextWalletID, sizeof(nextWalletID));
    
    // Lưu data cho từng wallet
    for (int i = 0; i<walletsCount; i++){
        wallets[i].save(ofs);
    }
}

void ManagerWallet::load(const string& filename){
    ifstream ifs(filename, ios::binary);
    if (!ifs){
        cout << "Cannot open Wallet file to load" << endl;
        return;
    }
    
    int walletsCount;
    ifs.read((char*)&walletsCount, sizeof(walletsCount));
    ifs.read((char*)&nextWalletID, sizeof(nextWalletID));
    
    wallets.clear();
    
    ifstream nameIfs(namePoolFile, ios::binary);

    for (int i = 0; i<walletsCount; i++) {
        Wallet w;
        w.load(ifs);
        if (nameIfs){w.loadName(nameIfs);}
        
        wallets.add(w);
    }
}
