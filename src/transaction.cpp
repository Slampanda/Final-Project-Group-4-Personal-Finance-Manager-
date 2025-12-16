#include "transaction.h"
using namespace std;
Transaction::Transaction(const Date& date, double amount, int walletID, int id,const string& description
) : date(date), amount(amount), walletID(walletID), id(id), description(description) {}

void Transaction::setDate(const Date& date) {
    this->date = date;
}
void Transaction::setAmount(double amount) {
    this->amount = amount;
}
void Transaction::setWalletID(int walletID) {
    this->walletID = walletID;
}
void Transaction::setDescription(const string& description) {
    this->description = description;
}

int Transaction::getID() const {
    return id;
} 
Date Transaction::getDate() const {
    return date;
}
double Transaction::getAmount() const{
    return amount;
}
int Transaction::getWalletID() const{
    return walletID;
}
string Transaction::getDescription() const{
    return description;
}
void Transaction::saveInfor(std::ofstream& ofs) const {
    ofs.write(reinterpret_cast<const char*>(&id), sizeof(id));
    ofs.write(reinterpret_cast<const char*>(&amount), sizeof(amount));
    ofs.write(reinterpret_cast<const char*>(&walletID), sizeof(walletID));
    date.save(ofs);
    size_t len = description.size();
    ofs.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len>0) {
        ofs.write(description.data(), len);
    }
}
void Transaction::loadInfor(std::ifstream& ifs) {
    ifs.read(reinterpret_cast<char*>(&id), sizeof(id));
    ifs.read(reinterpret_cast<char*>(&amount), sizeof(amount));
    ifs.read(reinterpret_cast<char*>(&walletID), sizeof(walletID));
    date.load(ifs);
    size_t len;
    ifs.read(reinterpret_cast<char*>(&len), sizeof(len));
    description.resize(len);
    if (len>0) {
        ifs.read(&description[0], len);
    }
}
