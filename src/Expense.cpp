#include "Expense.h"

Expense :: Expense (
    const Date &date,
    double amount,
    int id,
    int walletID,
    const std::string &description,
    int categoryID
) : Transaction(date, amount, id, walletID, description) , categoryID(categoryID) {};

void Expense::setCategoryID(int categoryID) {
    this->categoryID = categoryID;
}
int Expense::getCategoryID() const {
    return categoryID;
}

void Expense::save(std::ofstream &ofs) const{
    ofs.write(reinterpret_cast<const char*>(&amount), sizeof(amount));
    ofs.write(reinterpret_cast<const char*>(&id), sizeof(id));
    ofs.write(reinterpret_cast<const char*>(&walletID), sizeof(walletID));
    date.save(ofs);
    size_t len = description.size();
    ofs.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len>0) {
        ofs.write(description.data(), len);
    }
    ofs.write(reinterpret_cast<const char*>(&categoryID), sizeof(categoryID));
}
void Expense::load(std::ifstream &ifs) {
    ifs.read(reinterpret_cast<char*>(&amount), sizeof(amount));
    ifs.read(reinterpret_cast<char*>(&id), sizeof(id));
    ifs.read(reinterpret_cast<char*>(&walletID), sizeof(walletID));
    date.load(ifs);
    size_t len;
    ifs.read(reinterpret_cast<char*>(&len), sizeof(len));
    description.resize(len);
    if (len > 0) {
        ifs.read(&description[0], len);
    }
    ifs.read(reinterpret_cast<char*>(&categoryID), sizeof(categoryID));
}