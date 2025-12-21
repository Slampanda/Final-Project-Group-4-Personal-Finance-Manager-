#pragma once
#include "date.h"
#include <string>

enum class RecurringType{MONTHLY};

class RecurringTransaction{
private:
    int id;
    bool isIncome;
    double amount;
    int walletID;
    int sourceCategoryID;
    std::string description;
    Date startDate;
    Date endDate;
    RecurringType type;
    Date lastProcessed;
    int processedMonths; // Đếm số tháng đã xử lý

public:
    RecurringTransaction(int id = 0,
                         bool isIncome = false,
                         double amount = 0,
                         int walletID = 0,
                         int sourceCategoryID = 0,
                         const std::string& description = "",
                         const Date& start = Date(),
                         const Date& end = Date(0, 0, 0),
                         RecurringType type = RecurringType::MONTHLY
                         );
    
    bool shouldProcess(const Date& currentDate) const;
    void process(class TransactionManager& tm, Date processDate);
    void save(std::ofstream& ofs) const;
    void load(std::ifstream& ifs);
    
    // Getters
    int getID() const{return id;}
    
    bool getIsIncome() const{return isIncome;}
    
    double getAmount() const{return amount;}
    
    int getWalletID() const{return walletID;}
    
    int getSourceCategoryID() const{return sourceCategoryID;}
    
    std::string getDescription() const{return description;}
    
    Date getStartDate() const{return startDate;}
    
    Date getEndDate() const{return endDate;}
    
    void setLastProcessed(Date date){lastProcessed = date;}
};
