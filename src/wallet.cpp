#include "common.h"
#include "wallet.h"

Wallet::Wallet(int id, const string &name, double balance, size_t nameLen, long long nameOffset)
: id(id), name(name), balance(balance), nameLen(nameLen), nameOffset(nameOffset){}

int Wallet::getId() const{return id;}
string Wallet::getName() const{return name;}
double Wallet::getBalance() const{return balance;}
size_t Wallet::getNameLen() const{return nameLen;}
long long Wallet::getNameOffset() const{return nameOffset;}

void Wallet::setBalance(double newBalance){balance = newBalance;}

void Wallet::save(ofstream &ofs) const{
    ofs.write((char*)&id, sizeof(id));
    ofs.write((char*)&balance, sizeof(balance));
    ofs.write((char*)&nameLen, sizeof(nameLen));
    ofs.write((char*)&nameOffset, sizeof(nameOffset));
}

void Wallet::load(ifstream &ifs){
    ifs.read((char*)&id, sizeof(id));
    ifs.read((char*)&balance, sizeof(balance));
    ifs.read((char*)&nameLen, sizeof(nameLen));
    ifs.read((char*)&nameOffset, sizeof(nameOffset));
}

void Wallet::loadName(ifstream &ifs){
    if (nameOffset == -1 || nameLen <= 0){return;}
    ifs.seekg(nameOffset);
    name.resize(nameLen);
    ifs.read(&name[0], nameLen);
}
