#pragma once
#include "transactionManager.h"
#include "walletManager.h"
#include "incomeSourceManager.h"
#include "expenseCategoryManager.h"
#include "dynamicArray.h"
#include "recurringTransaction.h"
#include <string>

class FinanceManager{
private:
    TransactionManager transactionManager;
    ManagerWallet walletManager;
    SourceManager sourceManager;
    CategoryManager categoryManager;
    DynamicArray<RecurringTransaction> recurringTransactions;
    
    // Tên file
    const std::string WALLET_FILE = "/Users/macair/Downloads/PersonalFinanceManager/PersonalFinanceManager/data/wallets.bin";
    const std::string SOURCE_FILE = "/Users/macair/Downloads/PersonalFinanceManager/PersonalFinanceManager/data/sources.bin";
    const std::string CATEGORY_FILE = "/Users/macair/Downloads/PersonalFinanceManager/PersonalFinanceManager/data/categories.bin";
    const std::string TRANSACTION_FILE = "/Users/macair/Downloads/PersonalFinanceManager/PersonalFinanceManager/data/transactions.bin";
    const std::string RECURRING_FILE = "/Users/macair/Downloads/PersonalFinanceManager/PersonalFinanceManager/data/recurring.bin";
    
    const std::string WALLET_NAME_FILE = "/Users/macair/Downloads/PersonalFinanceManager/PersonalFinanceManager/data/walletNames.bin";
    const std::string SOURCE_NAME_FILE = "/Users/macair/Downloads/PersonalFinanceManager/PersonalFinanceManager/data/sourceNames.bin";
    const std::string CATEGORY_NAME_FILE = "/Users/macair/Downloads/PersonalFinanceManager/PersonalFinanceManager/data/categoryNames.bin";

    int nextRecurringId = 1;

public:
    FinanceManager();
    
    // Core methods
    void loadAllData();
    void saveAllData() const;
    void processRecurringTransactions();
    
    // Dashboard
    void showDashboard() const;
    
    // Statistics
    void showStatistics();
    void showTimeBasedStats(const Date& start, const Date& end) const;
    void showYearlyStats(int year) const;
    void showWalletStats(int walletID, const Date& start, const Date& end) const;
    void showIncomeBreakdown(const Date& start, const Date& end) const;
    void showExpenseBreakdown(const Date& start, const Date& end) const;
    void showNetBalanceReport(const Date& start, const Date& end) const;
    
    // Menu handlers
    void handleAddIncome();
    void handleAddExpense();
    void handleAddRecurring();
    void handleViewAllTransactions();
    void handleManageWallets();
    void handleManageSources();
    void handleManageCategories();
    
    // Main loop
    void run();
    
    // Helper methods
    Date inputDate(const std::string& prompt) const;
    std::string inputLine(const std::string& prompt) const;
    double inputAmount(const std::string& prompt) const;
    
    int selectWallet();
    int selectIncomeSource();
    int selectExpenseCategory();
    
private:
    void initializeSampleData();
};
