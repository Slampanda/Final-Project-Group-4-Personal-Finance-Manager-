#include "common.h"
#include "transactionManager.h"
#include "numberUtils.h"

string formatNumber(double number);

TransactionManager :: TransactionManager () : nextTransaction(1){}

void TransactionManager::addIncome(const Date& date,
                                   double amount,
                                   int walletID,
                                   int sourceID,
                                   const string &description
                                   ){
    Income inc(date,
               amount,
               nextTransaction++,
               walletID, //hình như cái này là walletID á, bị lộn với ở trên
               sourceID,
               description
               );
    incomes.add(inc);
    cout << "Income added. Wallet " << walletID << " increased by " << formatNumber(amount) << endl;
}

void TransactionManager::addExpense(const Date& date,
                                    double amount,
                                    int walletID,
                                    int categoryID,
                                    const string &description
                                    ){
    Expense exp(date,
                amount,
                nextTransaction++,
                walletID,
                categoryID,
                description
                );
    expenses.add(exp);
    cout << "Expense added. Wallet " << walletID << " decreased by " << formatNumber(amount) << endl;
}

void TransactionManager::showIncome(const ManagerWallet &mw, const SourceManager &im) const{
    cout << "================== LIST INCOMES ==================" << endl;
    cout << left
         << setw(6)  << "ID"
         << setw(12) << "Date"
         << setw(18) << "AMOUNT"
         << setw(15) << "WALLET"
         << setw(15) << "SOURCE"
         << endl;
    cout << "--------------------------------------------------" << endl;
    for (int i = 0; i<incomes.getSize(); i++){
        const Income& inc = incomes[i];
        
        string amountFormmated = formatNumber(inc.getAmount());

        cout << left
             << setw(6)  << inc.getID()
             << setw(12) << inc.getDate()
             << setw(18) << amountFormmated
             << setw(15) << mw.getWalletNameFromId(inc.getWalletID())
             << setw(15) << im.getSourceNameFromId(inc.getSourceID())
             << endl;
    }

    cout << "--------------------------------------------------" << endl;
    
    string totalFormatted = formatNumber(getTotalIncome());
    cout << "Total income: " << totalFormatted << endl;
}

void TransactionManager::showExpense(const ManagerWallet &mw, const CategoryManager &cm) const{
    cout << "==================LIST EXPENSES==================" << endl;
    cout << left
         << setw(6) << "ID"
         << setw(12) << "Date"
         << setw(18) << "AMOUNT"
         << setw(15) << "WALLET"
         << setw(15) << "Category"
         << endl;
    cout << "--------------------------------------------------" << endl;
    for (int i = 0; i<expenses.getSize(); i++){
        const Expense& exp = expenses[i];
        
        string amountFormatted = formatNumber(exp.getAmount());
        
        cout << left
             << setw(6) << exp.getID()
             << setw(12) << exp.getDate()
             << setw(18) << amountFormatted
             << setw(15) << mw.getWalletNameFromId(exp.getWalletID())
             << setw(15) << cm.getCategoryNameFromId(exp.getCategoryID())
             << endl;
    }
    
    cout << "-----------------------------------------------" << endl;
    string totalFormatted = formatNumber(getTotalExpense());
    cout << "Total expense: " << totalFormatted << endl;
}

double TransactionManager::getTotalIncome() const{
    double suminc = 0;
    for (int i = 0; i<incomes.getSize(); i++){
        suminc += incomes[i].getAmount();
    }
    return suminc;
}

double TransactionManager::getTotalExpense() const{
    double sumexp = 0;
    for (int i = 0; i<expenses.getSize(); i++) {
        sumexp += expenses[i].getAmount();
    }
    return sumexp;
}

double TransactionManager::getTotalIncomeBetween(const Date& start, const Date& end) const{
    double total = 0;
    for (int i = 0; i<incomes.getSize(); i++){
        Date d = incomes[i].getDate();
        if (start <= d && d <= end){
            total += incomes[i].getAmount();
        }
    }
    return total;
}

double TransactionManager::getTotalExpenseBetween(const Date& start, const Date& end) const{
    double total = 0;
    for (int i = 0; i<expenses.getSize(); i++){
        Date d = expenses[i].getDate();
        if (start <= d && d <= end){
            total += expenses[i].getAmount();
        }
    }
    return total;
}

double TransactionManager::getWalletIncomeBetween(int walletID, const Date& start, const Date& end) const{
    double total = 0;
    for (int i = 0; i<incomes.getSize(); i++){
        if (incomes[i].getWalletID() == walletID){
            Date d = incomes[i].getDate();
            if (start <= d && d <= end){
                total += incomes[i].getAmount();
            }
        }
    }
    return total;
}

double TransactionManager::getWalletExpenseBetween(int walletID, const Date& start, const Date& end) const{
    double total = 0;
    for (int i = 0; i<expenses.getSize(); i++){
        if (expenses[i].getWalletID() == walletID){
            Date d = expenses[i].getDate();
            if (start <= d && d <= end){
                total += expenses[i].getAmount();
            }
        }
    }
    return total;
}

void TransactionManager::showAllTransactions(const ManagerWallet &mw, const SourceManager &im, const CategoryManager &cm) const{
    cout << "\n====== ALL TRANSACTIONS (SORTED BY DATE) ======" << endl;
    
    DynamicArray<const Transaction*> allTransactions;
    
    // Add incomes
    for (int i = 0; i<incomes.getSize(); i++){
        allTransactions.add(&incomes[i]);
    }
    
    // Add expenses
    for (int i = 0; i<expenses.getSize(); i++){
        allTransactions.add(&expenses[i]);
    }
    
    // Simple bubble sort by date (ascending)
    for (int i = 0; i<allTransactions.getSize() - 1; i++){
        for (int j = 0; j<allTransactions.getSize() - i - 1; j++){
            if (allTransactions[j] -> getDate() > allTransactions[j+1] -> getDate()){
                // Swap pointers
                const Transaction* temp = allTransactions[j];
                allTransactions[j] = allTransactions[j+1];
                allTransactions[j+1] = temp;
            }
        }
    }
    
    // Display header
    cout << left
         << setw(8) << "ID"
         << setw(10) << "Type"
         << setw(12) << "Date"
         << setw(20) << "Amount"
         << setw(20) << "Wallet"
         << setw(20) << "Source/Category" << endl;
    cout << "--------------------------------------------------" << endl;

    // Display each transaction
    for (int i = 0; i<allTransactions.getSize(); i++){
        const Transaction* t = allTransactions[i];
        
        string amountFormatted = formatNumber(t -> getAmount());
        
        cout << left
             << setw(8) << t -> getID()
             << setw(10) << (t -> getIsIncome() ? "INCOME" : "EXPENSE")
             << setw(12) << t -> getDate()
             << setw(20) << amountFormatted
             << setw(20) << mw.getWalletNameFromId(t -> getWalletID());
        
        if (t -> getIsIncome()){
            cout << setw(20) << im.getSourceNameFromId(t -> getSourceCategoryID());
        }
        else{
            cout << setw(20) << cm.getCategoryNameFromId(t -> getSourceCategoryID());
        }
        cout << endl;
    }
    
    // Display summary
    cout << "--------------------------------------------------" << endl;
    cout << "Total Transactions: " << allTransactions.getSize()
         << " (Income: " << incomes.getSize()
         << ", Expense: " << expenses.getSize() << ")" << endl;
}

DynamicArray<pair<int, double>> TransactionManager::getIncomeBySource(const Date& start, const Date& end) const {
    // Use a simple array to accumulate amounts by source ID
    struct SourceTotal {
        int sourceID;
        double total;
    };
    
    // Find all unique source IDs in the date range
    DynamicArray<int> sourceIDs;
    for (int i = 0; i < incomes.getSize(); i++) {
        Date d = incomes[i].getDate();
        if (start <= d && d <= end) {
            int sourceId = incomes[i].getSourceID();
            bool found = false;
            for (int j = 0; j < sourceIDs.getSize(); j++) {
                if (sourceIDs[j] == sourceId) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                sourceIDs.add(sourceId);
            }
        }
    }
    
    // Calculate totals for each source
    DynamicArray<pair<int, double>> result;
    for (int i = 0; i < sourceIDs.getSize(); i++) {
        int sourceId = sourceIDs[i];
        double total = 0;
        
        for (int j = 0; j < incomes.getSize(); j++) {
            Date d = incomes[j].getDate();
            if (start <= d && d <= end && incomes[j].getSourceID() == sourceId) {
                total += incomes[j].getAmount();
            }
        }
        
        result.add(make_pair(sourceId, total));
    }
    
    return result;
}

DynamicArray<pair<int, double>> TransactionManager::getExpenseByCategory(const Date& start, const Date& end) const {
    // Similar implementation for expense categories
    DynamicArray<int> categoryIDs;
    for (int i = 0; i < expenses.getSize(); i++) {
        Date d = expenses[i].getDate();
        if (start <= d && d <= end) {
            int catId = expenses[i].getCategoryID();
            bool found = false;
            for (int j = 0; j < categoryIDs.getSize(); j++) {
                if (categoryIDs[j] == catId) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                categoryIDs.add(catId);
            }
        }
    }
    
    DynamicArray<pair<int, double>> result;
    for (int i = 0; i < categoryIDs.getSize(); i++) {
        int catId = categoryIDs[i];
        double total = 0;
        
        for (int j = 0; j < expenses.getSize(); j++) {
            Date d = expenses[j].getDate();
            if (start <= d && d <= end && expenses[j].getCategoryID() == catId) {
                total += expenses[j].getAmount();
            }
        }
        
        result.add(make_pair(catId, total));
    }
    
    return result;
}

// Recent transactions
DynamicArray<const Transaction*> TransactionManager::getRecentTransactions(int limit) const {
    DynamicArray<const Transaction*> recent;
    
    // Get all transactions
    DynamicArray<const Transaction*> allTransactions;
    for (int i = 0; i < incomes.getSize(); i++) {
        allTransactions.add(&incomes[i]);
    }
    for (int i = 0; i < expenses.getSize(); i++) {
        allTransactions.add(&expenses[i]);
    }
    
    // Sort by date (most recent first)
    for (int i = 0; i < allTransactions.getSize() - 1; i++) {
        for (int j = 0; j < allTransactions.getSize() - i - 1; j++) {
            if (allTransactions[j]->getDate() < allTransactions[j+1]->getDate()) {
                const Transaction* temp = allTransactions[j];
                allTransactions[j] = allTransactions[j+1];
                allTransactions[j+1] = temp;
            }
        }
    }
    
    // Get limited number
    int count = (limit < allTransactions.getSize()) ? limit : allTransactions.getSize();
    for (int i = 0; i < count; i++) {
        recent.add(allTransactions[i]);
    }
    
    return recent;
}

void TransactionManager::save(const string &filename) const {
    ofstream ofs(filename.c_str(), ios::binary);
    if (!ofs){
        cout << "Cannot open Transactions file to save" << endl;
        return;
    }
    ofs.write((char*)&nextTransaction, sizeof(nextTransaction));
    int sizeinc = incomes.getSize();
    int sizeexp = expenses.getSize();
    ofs.write((char*)&sizeinc, sizeof(sizeinc));
    for (int i = 0; i<sizeinc; i++) {
        incomes[i].save(ofs);
    }
    ofs.write((char*)&sizeexp, sizeof(sizeexp));
    for (int i = 0; i<sizeexp; i++) {
        expenses[i].save(ofs);
    }
}
void TransactionManager::load(const string &filename) {
    ifstream ifs(filename.c_str(), ios::binary);
    if (!ifs){
        cout << "Cannot open Transactions file to load" << endl;
        return;
    }
    incomes.clear();
    expenses.clear();
    ifs.read((char*)&nextTransaction, sizeof(nextTransaction));
    int sizeinc;
    ifs.read((char*)&sizeinc, sizeof(sizeinc));
    for (int i = 0; i < sizeinc; i++) {
        Income inc;
        inc.load(ifs);
        incomes.add(inc);
    }
    int sizeexp;
    ifs.read((char*)&sizeexp, sizeof(sizeexp));
    for (int i = 0; i < sizeexp; i++) {
        Expense exp;
        exp.load(ifs);
        expenses.add(exp);
    }
}

