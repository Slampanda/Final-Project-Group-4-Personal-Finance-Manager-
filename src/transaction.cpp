#include "common.h"
#include "transaction.h"

Transaction::Transaction(const Date& date,
                         double amount,
                         int id,
                         int walletID,
                         bool isIncome,
                         int sourceCategoryID,
                         const string& description
                         )
: date(date), amount(amount), id(id), walletID(walletID), isIncome(isIncome), sourceCategoryID(sourceCategoryID), description(description){}

void Transaction::setDate(const Date& date){this -> date = date;}

void Transaction::setAmount(double amount){this -> amount = amount;}

void Transaction::setWalletID(int walletID){this -> walletID = walletID;}

void Transaction::setIsIncome(bool isIncome){this -> isIncome = isIncome;}

void Transaction::setSourceCategoryID(int sourceCategoryID){this -> sourceCategoryID = sourceCategoryID;}

void Transaction::setDescription(const string& description){this -> description = description;}

int Transaction::getID() const{return id;}

Date Transaction::getDate() const{return date;}

double Transaction::getAmount() const{return amount;}

int Transaction::getWalletID() const{return walletID;}

bool Transaction::getIsIncome() const{return isIncome;}

int Transaction::getSourceCategoryID() const{return sourceCategoryID;}

string Transaction::getDescription() const{return description;}

void Transaction::saveInfor(ofstream& ofs) const{
    // id (4 bytes)
    ofs.write(reinterpret_cast<const char*>(&id), sizeof(id));
    // date (12 bytes)
    date.save(ofs);
    // isIncome (1 byte)
    ofs.write(reinterpret_cast<const char*>(&isIncome), sizeof(isIncome));
    // source/categoryID (4 bytes)
    ofs.write(reinterpret_cast<const char*>(&sourceCategoryID), sizeof(sourceCategoryID));
    // amount (8 bytes)
    ofs.write(reinterpret_cast<const char*>(&amount), sizeof(amount));
    // walletID (4 bytes)
    ofs.write(reinterpret_cast<const char*>(&walletID), sizeof(walletID));
    
}

void Transaction::loadInfor(ifstream& ifs){
    ifs.read(reinterpret_cast<char*>(&id), sizeof(id));
    date.load(ifs);
    ifs.read(reinterpret_cast<char*>(&isIncome), sizeof(isIncome));
    ifs.read(reinterpret_cast<char*>(&sourceCategoryID), sizeof(sourceCategoryID));
    ifs.read(reinterpret_cast<char*>(&amount), sizeof(amount));
    ifs.read(reinterpret_cast<char*>(&walletID), sizeof(walletID));
}
