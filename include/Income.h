#pragma once
#include "transaction.h"

class Income : public Transaction {
private:
    int sourceID;
public:
    Income (const Date& date = Date(), double amount=0, int id = 0, int walletID = 0, const std::string& description= "", int sourceID = 0);
    void setSourceID(int soucreID);
    int getSourceID()const;
    void save(std::ofstream &ofs) const override;
    void load(std::ifstream &ifs) override;
};