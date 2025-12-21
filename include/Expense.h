#pragma once
#include "transaction.h"

class Expense : public Transaction {
private:
    int categoryID;
public:
    Expense(const Date &date = Date(),
            double amount = 0,
            int id = 0,
            int walletID = 0,
            int categoryID = 0,
            const std::string &description = ""
            );
    
    void save(std::ofstream &ofs) const override;
    void load(std::ifstream &ifs) override;
    
    void setCategoryID(int categoryID);
    int getCategoryID() const;
};
