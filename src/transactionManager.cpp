#include "transactionManager.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

TransactionManager :: TransactionManager () : nextTransaction(1){}

void TransactionManager::addIncome(
        const Date& date,
        double amount,
        int walletID,
        int sourceID,
        const std::string &description
    ) {
        Income inc(
            date,
            amount,
            walletID,
            nextTransaction++,
            description,
            sourceID
        );
        incomes.add(inc);
    }

void TransactionManager::addExpense(
        const Date& date,
        double amount,
        int walletID,
        int categoryID,
        const std::string &description
    ) {
        Expense exp(
            date,
            amount,
            walletID,
            nextTransaction++,
            description,
            categoryID
        );
        expenses.add(exp);
    }
void TransactionManager::showIncome(const ManagerWallet &mw, const IncomeSourceManager &im) const {
    cout << "================== LIST INCOMES ==================\n";
    cout << left
         << setw(6)  << "ID"
         << setw(12) << "Date"
         << setw(12) << "AMOUNT"
         << setw(12) << "WALLET"
         << setw(12) << "SOURCE"
         << endl;
    cout << "--------------------------------------------------\n";
    for (int i = 0; i < incomes.getSize(); i++) {
        const Income& inc = incomes[i];

        cout << left
             << setw(6)  << inc.getID()
             << setw(12) << inc.getDate()
             << setw(12) << fixed << setprecision(0) << inc.getAmount()
             << setw(12) << mw.getWalletNameFromId(inc.getWalletID())
             << setw(12) << im.getSourceNameFromId(inc.getSourceID())
             << endl;
    }

    cout << "--------------------------------------------------\n";
    cout << "Total income: " << getTotalIncome() << endl;
}
void TransactionManager::showExpense(const ManagerWallet &mw, const CategoryManager &cm) const {
    cout << "==================LIST EXPENSES==================" << endl;
    cout << setfill(' ');
    cout << left << setw(6) << "ID"
                 << setw(12) << "Date"
                 << setw(12) << "AMOUNT"
                 << setw(12) << "WALLET"
                 << setw(12) << "Category"
                 << endl;
    for (int i=0; i<50; i++) {
        cout << "-";
    }
    cout << endl;
    cout << setfill(' ');
    for (int i=0; i<expenses.getSize(); i++) {
        const Expense &exp = expenses[i];
        cout << left << setw(6) << exp.getID()
                     << setw(12) << exp.getDate()
                     << setw(12) << fixed << setprecision(0) << exp.getAmount()
                     << setw(12) << mw.getWalletNameFromId(exp.getWalletID())
                     << setw(12) << cm.getCategoryNameFromId(exp.getCategoryID())
                     << endl;
    }
    cout << "-----------------------------------------------\n";
    cout << "Total expense: " << getTotalExpense() << endl;
}

double TransactionManager::getTotalIncome() const {
    double suminc = 0;
    for (int i=0; i<incomes.getSize(); i++) {
        suminc += incomes[i].getAmount();
    }
    return suminc;
}
double TransactionManager::getTotalExpense() const {
    double sumexp = 0;
    for (int i=0; i<expenses.getSize(); i++) {
        sumexp+= expenses[i].getAmount();
    }
    return sumexp;
}

void TransactionManager::save(const std::string &filename) const {
    ofstream ofs(filename.c_str(), ios::binary);
    if (!ofs) return;
    ofs.write((char*)&nextTransaction, sizeof(nextTransaction));
    int sizeinc = incomes.getSize();
    int sizeexp = expenses.getSize();
    ofs.write((char*)&sizeinc, sizeof(sizeinc));
    for (int i=0; i<sizeinc; i++) {
        incomes[i].save(ofs);
    }
    ofs.write((char*)&sizeexp, sizeof(sizeexp));
    for (int i=0; i<sizeexp; i++) {
        expenses[i].save(ofs);
    }
}
void TransactionManager::load(const std::string &filename) {
    ifstream ifs(filename.c_str(), ios::binary);
    if (!ifs) return;
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
