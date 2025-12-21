#include "common.h"
#include "income.h"

Income::Income(const Date& date,
               double amount,
               int id,
               int walletID,
               int sourceID,
               const string& description
               )
: Transaction(date, amount, id, walletID, true, sourceID, description){}

void Income::setSourceID(int sourceID){
    this->sourceID = sourceID;
    setSourceCategoryID(sourceID);
}

int Income::getSourceID() const{
    return sourceID;
}

void Income::save(ofstream &ofs) const{
    saveInfor(ofs);
}

void Income::load(ifstream &ifs){
    loadInfor(ifs);
}
