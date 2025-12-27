#include "common.h"
#include "walletManager.h"
#include "numberUtils.h"

WalletManager::WalletManager(const string& nameFile) : namePoolFile("data/walletNames.bin"), nextWalletID(1){}

long long WalletManager::calculateNameOffset() const{
    long long currentOffset = 0;
        
    for (int i = 0; i<wallets.getSize(); i++){
        const_cast<Wallet&>(wallets[i]).setNameOffset(currentOffset);
        const_cast<Wallet&>(wallets[i]).setNameLen(wallets[i].getName().length());
            
        currentOffset += wallets[i].getNameLen();
    }
    return currentOffset;
}

int WalletManager::addWallet(const string& name, double initialBalance){
    Wallet newWallet(nextWalletID, name, initialBalance, name.length(), -1);
    wallets.add(newWallet);
        
    cout << "Wallet added (temporary). ID: " << nextWalletID << ", Name: " << name << endl;
        
    return nextWalletID++;
}

string WalletManager::getWalletNameFromId(int id) const{
    for (int i = 0; i<wallets.getSize(); i++){
        if (wallets[i].getId() == id){
            return wallets[i].getName();
        }
    }
    return "Unknown Wallet";
}

double WalletManager::getWalletBalance(int id) const{
    for (int i = 0; i<wallets.getSize(); i++){
        if (wallets[i].getId() == id){
            return wallets[i].getBalance();
        }
    }
    cout << "Unknown Wallet" << endl;
    return 0.0;
}

const Wallet& WalletManager::getWalletByIndex(int index) const{
    if (index < 0 || index >= wallets.getSize()){
        throw out_of_range("Wallet index out of range");
    }
    return wallets[index];
}

void WalletManager::updateWalletBalance(int id, double amount, bool isIncome){
    for (int i = 0; i<wallets.getSize(); i++){
        if (wallets[i].getId() == id){
            double currentBalance = wallets[i].getBalance();
            if (isIncome){currentBalance += amount;}
            else{currentBalance -= amount;}
            wallets[i].setBalance(currentBalance);
            cout << "✓ Updated wallet " << id << " balance: " << formatNumber(currentBalance) << endl;
            return ;
        }
    }
    cout << "✗ Wallet ID " << id << " not found!" << endl;
}

void WalletManager::renameWallet(int id, const std::string& newName){
    for (int i = 0; i<wallets.getSize(); i++){
        if (wallets[i].getId() == id){
            wallets[i].setName(newName);
            cout << "✓ Renamed Wallet " << id << " to: " << newName << endl;
            return;
        }
    }
    cout << "✗ Wallet ID " << id << " not found!" << endl;
}

void WalletManager::showWallets() const{
    cout << "============= WALLET LIST =============" << endl;
    for (int i = 0; i<wallets.getSize(); i++){
        cout << wallets[i].getId() << " - " << wallets[i].getName() << " - Balance: " << formatNumber(wallets[i].getBalance()) << endl;
    }
}

int WalletManager::getSize() const{return wallets.getSize();}

double WalletManager::getTotalBalance() const{
    double total = 0;
    for (int i = 0; i<wallets.getSize(); i++){
        total += wallets[i].getBalance();
    }
    return total;
}

void WalletManager::save(const string& filename) const{
    
    const_cast<WalletManager*>(this)->rebuildAndSaveNamePool();

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

void WalletManager::load(const string& filename){
    ifstream ifs(filename, ios::binary | ios::ate);
    if (!ifs){
        cout << "Cannot open Wallet file to load" << endl;
        return;
    }
    
    size_t fileSize = ifs.tellg();
    if (fileSize == 0) {
        cout << "Wallet file is empty" << endl;
        ifs.close();
        return;
    }
    
    ifs.seekg(0, ios::beg);
    
    int walletsCount;
    ifs.read((char*)&walletsCount, sizeof(walletsCount));
    ifs.read((char*)&nextWalletID, sizeof(nextWalletID));
    
    wallets.clear();
    
    ifstream nameIfs(namePoolFile, ios::binary);

    for (int i = 0; i<walletsCount; i++){
        Wallet w;
        w.load(ifs);
        if (nameIfs){w.loadName(nameIfs);}
        wallets.add(w);
    }
}

void WalletManager::rebuildAndSaveNamePool(){
    cout << "\n=== Rebuilding name pool ===" << endl;
        
    if (wallets.getSize() == 0){
        cout << "No wallets to save." << endl;
            
        ofstream ofs(namePoolFile, ios::binary | ios::trunc);
        ofs.close();
        return;
    }
        
    // Tính toán offsets và set cho từng wallet
    long long currentOffset = 0;
    for (int i = 0; i<wallets.getSize(); i++){
        size_t nameLen = wallets[i].getName().length();
        wallets[i].setNameLen(nameLen);
        wallets[i].setNameOffset(currentOffset);
        currentOffset += nameLen;
    }
        
    // Ghi toàn bộ tên vào file (truncate mode)
    ofstream ofs(namePoolFile, ios::binary | ios::trunc);
    if (!ofs){
        cout << "Cannot open name pool file!" << endl;
        return;
    }
    
    // Ghi tất cả tên
    for (int i = 0; i<wallets.getSize(); i++){
        const string& name = wallets[i].getName();
        ofs.write(name.c_str(), name.length());
    }
        
    ofs.close();
    cout << "Name pool saved!" << endl;
}
