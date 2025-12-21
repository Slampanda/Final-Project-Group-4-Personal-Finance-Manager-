#include "common.h"
#include "recurringTransaction.h"
#include "transactionManager.h"

RecurringTransaction::RecurringTransaction(int id,
                                           bool isIncome,
                                           double amount,
                                           int walletID,
                                           int sourceCategoryID,
                                           const string& description,
                                           const Date& start,
                                           const Date& end,
                                           RecurringType type
                                           )
: id(id), isIncome(isIncome), amount(amount), walletID(walletID), sourceCategoryID(sourceCategoryID), description(description), startDate(start), endDate(end), type(type), lastProcessed(Date()), processedMonths(0){}

bool RecurringTransaction::shouldProcess(const Date& currentDate) const{
    // Kiểm tra đã qua ngày bắt đầu chưa
    if (currentDate < startDate){return false;}
    
    // Kiểm tra đã hết hạn chưa (nếu có endDate)
    if (endDate.year != 0 && endDate.month != 0 && endDate.day != 0){
        if (currentDate > endDate){return false;}
    }
    
    // Kiểm tra đã xử lý tháng này chưa
    if (lastProcessed.year == currentDate.year && lastProcessed.month == currentDate.month){
        return false;
    }
    
    // Kiểm tra khoảng cách tháng
    int monthDiff = (currentDate.year - startDate.year)*12 + (currentDate.month - startDate.month);
    if (monthDiff < 0){return false;}
    return true;
}

void RecurringTransaction::process(TransactionManager& tm, Date processDate){
    if (isIncome){tm.addIncome(processDate, amount, walletID, sourceCategoryID, "");}
    
    else{tm.addExpense(processDate, amount, walletID, sourceCategoryID, "");}
    
    lastProcessed = processDate;
    processedMonths++;
    cout << "Processed recurring transaction ID: " << id << endl;
}

void RecurringTransaction::save(ofstream& ofs) const{
    ofs.write(reinterpret_cast<const char*>(&id), sizeof(id));
    ofs.write(reinterpret_cast<const char*>(&isIncome), sizeof(isIncome));
    ofs.write(reinterpret_cast<const char*>(&amount), sizeof(amount));
    ofs.write(reinterpret_cast<const char*>(&walletID), sizeof(walletID));
    ofs.write(reinterpret_cast<const char*>(&sourceCategoryID), sizeof(sourceCategoryID));
    
    // Lưu dates
    startDate.save(ofs);
    endDate.save(ofs);
    lastProcessed.save(ofs);
    
    // Lưu type
    int typeInt = static_cast<int>(type);
    ofs.write(reinterpret_cast<const char*>(&typeInt), sizeof(typeInt));
    
    ofs.write(reinterpret_cast<const char*>(&processedMonths), sizeof(processedMonths));
}

void RecurringTransaction::load(ifstream& ifs){
    ifs.read(reinterpret_cast<char*>(&id), sizeof(id));
    ifs.read(reinterpret_cast<char*>(&isIncome), sizeof(isIncome));
    ifs.read(reinterpret_cast<char*>(&amount), sizeof(amount));
    ifs.read(reinterpret_cast<char*>(&walletID), sizeof(walletID));
    ifs.read(reinterpret_cast<char*>(&sourceCategoryID), sizeof(sourceCategoryID));
    
    // Đọc dates
    startDate.load(ifs);
    endDate.load(ifs);
    lastProcessed.load(ifs);
    
    // Đọc type
    int typeInt;
    ifs.read(reinterpret_cast<char*>(&typeInt), sizeof(typeInt));
    type = static_cast<RecurringType>(typeInt);
    
    ifs.read(reinterpret_cast<char*>(&processedMonths), sizeof(processedMonths));
}
