#include "walletManager.h"
#include <fstream>
#include <iostream>
using namespace std;
ManagerWallet::ManagerWallet() : nextWalletID(1) {}

int ManagerWallet::addWallet(const std::string & name) {
    wallets.add(Wallet(nextWalletID, name));
    return nextWalletID++;
}
std::string ManagerWallet::getWalletNameFromId(int id) const {
    for (int i=0; i<wallets.getSize(); i++) {
        if (wallets[i].getId()==id) {
            return wallets[i].getName();
        }
    }
    return "Unknown Wallet";
}
void ManagerWallet::showWallets() const {
    cout << "====== WALLET LIST ======\n";
    for (int i = 0; i < wallets.getSize(); i++) {
        cout << wallets[i].getId() << " - " << wallets[i].getName() << endl;
    }
}
void ManagerWallet::save(const string& filename) const {
    std::ofstream ofs(filename.c_str(), std::ios::binary);
    if (!ofs) {
        cout << "Cannot open Wallet file to save\n";
        return;
    }
    ofs.write((char*)&nextWalletID, sizeof(nextWalletID));
    int len = wallets.getSize();
    ofs.write((char*)&len, sizeof(len));
    for (int i=9; i<len; i++) {
        wallets[i].save(ofs);
    }
}
void ManagerWallet::load(const string& filename) {
    std::ifstream ifs(filename.c_str(), std::ios::binary);
    if (!ifs) return;
    int len;
    ifs.read((char*)&len, sizeof(len));
    ifs.read((char*)&nextWalletID, sizeof(nextWalletID));
    wallets.clear();
    for (int i = 0; i < len; i++) {
        Wallet w;
        w.load(ifs);
        wallets.add(w);
    }
}