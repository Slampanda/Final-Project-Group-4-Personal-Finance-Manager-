#pragma once
#include "dynamicArray.h"
#include "income.h"
#include "expense.h"
#include "walletManager.h"
#include "incomeSourceManager.h"
#include "expenseCategoryManager.h"

struct SourceCategoryPair {
    int id;
    double amount;
    
    // Constructor default
    SourceCategoryPair() : id(0), amount(0.0) {}
    
    // Constructor với tham số
    SourceCategoryPair(int i, double a) : id(i), amount(a) {}
    
    // Copy constructor
    SourceCategoryPair(const SourceCategoryPair& other) : id(other.id), amount(other.amount) {}
};

class TransactionManager{
private:
    DynamicArray <Income> incomes;
    DynamicArray <Expense> expenses;
    int nextTransaction;
public:
    TransactionManager();

    // Core transaction method
    void addIncome(const Date& date,
                   double amount,
                   int walletID,
                   int sourceID,
                   const std::string &description
                   );
    void addExpense(const Date& date,
                    double amount,
                    int walletID,
                    int categoryID,
                    const std::string &description
                    );
    
    // Display method
    void showIncome(const WalletManager &wm, const SourceManager &im) const;
    void showExpense(const WalletManager &wm, const CategoryManager &cm) const;
    
    // Display all transaction (sorted by date)
    void showAllTransactions(const WalletManager &wm, const SourceManager &im, const CategoryManager &cm) const;
    
    // Basic statistics
    double getTotalIncome() const;
    double getTotalExpense() const;
    
    // Time-based statistics
    double getTotalIncomeBetween(const Date& start, const Date& end) const;
    double getTotalExpenseBetween(const Date& start, const Date& end) const;

    // Wallet-based statistics
    double getWalletIncomeBetween(int walletID, const Date& start, const Date& end) const;
    double getWalletExpenseBetween(int walletID, const Date& start, const Date& end) const;

    // Breakdown statistics
    DynamicArray<std::pair<int, double>> getIncomeBySource(const Date& start, const Date& end) const;
    DynamicArray<std::pair<int, double>> getExpenseByCategory(const Date& start, const Date& end) const;
        
    // Wallet-specific breakdown
    DynamicArray<std::pair<int, double>> getWalletIncomeBySource(int walletID,
                                                                 const Date& start,
                                                                 const Date& end
                                                                 ) const;
        
    DynamicArray<std::pair<int, double>> getWalletExpenseByCategory(int walletID,
                                                                    const Date& start,
                                                                    const Date& end
                                                                    ) const;
        
    // Recent transactions
    DynamicArray<const Transaction*> getRecentTransactions(int limit = 10) const;
    DynamicArray<const Transaction*> getRecentWalletTransactions(int walletID, int limit = 10) const;
    
    int getIncomeCount() const{return incomes.getSize();}
    int getExpenseCount() const{return expenses.getSize();}
    int getTotalCount() const{return incomes.getSize() + expenses.getSize();}
    
    void save(const std::string &filename) const;
    void load(const std::string &filename);
};
