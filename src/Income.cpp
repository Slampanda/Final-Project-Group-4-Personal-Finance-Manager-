#include "Income.h"

Income::Income(
    const Date& date,
    double amount,
    int id,
    int walletID,
    const std::string& description,
    int sourceID
) : Transaction(date, amount, id, walletID, description) , sourceID(sourceID) {}

void Income::setSourceID(int sourceID) {
    this->sourceID = sourceID;
}
int Income::getSourceID() const {
    return sourceID;
}

void Income::save(std::ofstream &ofs) const {
    saveInfor(ofs);
    ofs.write(reinterpret_cast<const char*>(&sourceID), sizeof(sourceID));
}
void Income::load(std::ifstream &ifs) {
    loadInfor(ifs);
    ifs.read(reinterpret_cast<char*>(&sourceID), sizeof(sourceID));
}