#pragma once
#include "transaction.h"

class Expense : public Transaction {
private:
    int categoryID;
public:
    Expense(
        const Date &date = Date(),
        double amount = 0,
        int id = 0,
        int walletID= 0,
        const std::string &description = "",
        int categoryID = 0
    );
    void setCategoryID(int categoryID);
    int getCategoryID() const;
    void save(std::ofstream &ofs) const override;
    void load(std::ifstream &ifs) override;
};