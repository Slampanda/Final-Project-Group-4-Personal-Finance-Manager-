#pragma once
#include "dynamicArray.h"
#include "Income.h"
#include "Expense.h"
#include "walletManager.h"
#include "incomeSourceManager.h"
#include "expenseCategoryManager.h"

class TransactionManager{
private:
    DynamicArray <Income> incomes;
    DynamicArray <Expense> expenses;
    int nextTransaction;
public:
    TransactionManager();

    void addIncome(
        const Date& date,
        double amount,
        int walletID,
        int sourceID,
        const std::string &description
    );
    void addExpense(
        const Date& date,
        double amount,
        int walletID,
        int categoryID,
        const std::string &description
    );
    
    void showIncome(const ManagerWallet &mw, const IncomeSourceManager &im) const;
    void showExpense(const ManagerWallet &mw, const CategoryManager &cm) const;
    double getTotalIncome() const;
    double getTotalExpense() const;
    void save(const std::string &filename) const;
    void load(const std::string &filename);
};
