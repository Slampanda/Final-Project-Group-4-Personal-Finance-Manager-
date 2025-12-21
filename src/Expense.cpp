#include "common.h"
#include "expense.h"

Expense :: Expense (const Date &date,
                    double amount,
                    int id,
                    int walletID,
                    int categoryID,
                    const string &description
                    )
: Transaction(date, amount, id, walletID, false, categoryID, description){};

void Expense::setCategoryID(int categoryID){
    this->categoryID = categoryID;
    setSourceCategoryID(categoryID);
}

int Expense::getCategoryID() const{
    return categoryID;
}

void Expense::save(ofstream &ofs) const{
    saveInfor(ofs);
}

void Expense::load(ifstream &ifs){
    loadInfor(ifs);
}
