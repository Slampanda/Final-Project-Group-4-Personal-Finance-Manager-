#pragma once
#include "dynamicArray.h"
#include "transaction.h"
#include "wallet.h"
#include "incomeSource.h"
#include "expenseCategory.h"

class TransactionManager{
private:
    DynamicArray <Transaction> transactions;
    DynamicArray <Wallet> wallets;
    DynamicArray <IncomeSource> incomeSources;
    DynamicArray <ExpenseCategory> expenseCategories;
    
    int nextTransactionID;
    int nextWalletID;
    int nextSourceID;
    int nextCategoryID;

    Wallet* findWalletByID(int walletID);
    IncomeSource* findSourceByID(int sourceID);
    ExpenseCategory* findCategoryByID(int categoryID);
    
public:
    TransactionManager();
    
    // MASTER DATA
    // Wallet management
    int addWallet(string name, double initialBalance);
    string getWalletName(int walletID);
    double getWalletBalance(int walletID);
    void updateWalletBalance(int walletID, double amount, bool isIncome);
    
    // Income source management
    int addSource(string name);
    string getSourceName(int sourceID);
    
    // Expense category management
    int addCategory(string name);
    string getCategoryName(int categoryID);
    
    // TRANSACTION MANAGEMENT
    // Add income
    int addIncome(Date d, int sourceID, double amount, int walletID, string description);
    
    // Add expense
    int addExpense(Date d, int categoryID, double amount, int walletID, string description);
    
    // DISPLAY
    // 1 Transation
    void displayFullTransaction(const Transaction& t);
    
    // All transaction
    void displayAllTransactions();
    
    //
    void displayIncomeTrasactions();
    void displayExpenseTrasactions();
    
    // GETTERS
    int getTransactionCount() const;
    int getWalletCount() const;
    int getIncomeSourceCount() const;
    int getExpenseCategoryCount() const;
    
    // FIND
    Transaction* findFullTransactionByID(int ID);
    void displayTransactionsByWallet(int walletID);
    void displayTransactionsByDateRange(Date startDate, Date endDate);
    
    // FILE I/O
    bool saveToFile(string filename);
    bool loadFromFile(string filename);
};
