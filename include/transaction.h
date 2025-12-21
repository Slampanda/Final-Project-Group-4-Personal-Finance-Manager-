#pragma once
#include "date.h"
#include <string>

class Transaction{
protected:
    Date date;
    double amount;
    int id;
    int walletID;
    bool isIncome; //tui muốn thêm 2 cái này vào để lưu data về giao dịch cho dễ á
    int sourceCategoryID;
    std::string description;
public:
    Transaction(const Date& date = Date(),
                double amount = 0,
                int id = 0,
                int walletID = 0,
                bool isIncome = false,
                int sourceCategoryID = 0,
                const std::string& description = ""
                );
    virtual  ~Transaction() = default;

    void setDate(const Date& date);
    void setAmount(double amount);
    void setWalletID(int walletID);
    void setIsIncome(bool isIncome);
    void setSourceCategoryID(int sourceCategoryID);
    void setDescription(const std::string& description);

    int getID() const;
    Date getDate() const;
    double getAmount() const;
    int getWalletID() const;
    bool getIsIncome() const;
    int getSourceCategoryID() const;
    std::string getDescription() const;

    void saveInfor(std::ofstream& ofs) const;
    void loadInfor(std::ifstream& ifs);
    virtual void load(std::ifstream& ifs) = 0;
    virtual void save(std::ofstream& ofs) const = 0;

};

//Transaction createTransaction();
//void displayTransaction(const Transaction& t);
