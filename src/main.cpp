#include "transactionManager.h"
#include "date.h"
#include "expenseCategoryManager.h"
#include "IncomeSourceManager.h"
#include "walletManager.h"
#include <iostream>
#include <limits>
using namespace std;
Date inputDate() {
    int d, m, y;
    while (true) {
        cout << "Enter date (dd mm yyyy): ";
        cin >> d >> m >> y;
        try {
            return Date(d, m, y);
        } catch (...) {
            cout << "Invalid date, please re-enter.\n";
        }
    }
}
string inputLine(const string& prompt) {
    cout << prompt;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string s;
    getline(cin, s);
    return s;
}
int main(){
    TransactionManager tm;
    IncomeSourceManager ism;
    CategoryManager cm;
    ManagerWallet mw;
    mw.addWallet("Cash");
    mw.addWallet("Bank");
    mw.addWallet("Momo");
    ism.addSource("Salary");
    ism.addSource("Gift");
    ism.addSource("Part-Time");
    cm.addCategory("Food");
    cm.addCategory("Shopping");
    cm.addCategory("Transportation");
    cm.addCategory("Comestics");
    cm.addCategory("pig");

    int choice;
    do {
        cout << "===========Personal Finance Manager==========" << endl;
        cout << "1. Add incomes" << endl;
        cout << "2. Add expenses" << endl;
        cout << "3. Show incomes" << endl;
        cout << "4. Show expenses" << endl;
        cout << "0. Exit" << endl;
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
            Date date = inputDate();
            double amount;
            cout << "Enter amount: ";
            cin >> amount;
            mw.showWallets();
            int walletId;
            cout << "Choose wallet ID: ";
            cin >> walletId;
            ism.showSources();
            int sourceId;
            cout << "Choose source ID: ";
            cin >> sourceId;
            string desc = inputLine("Description: ");
            tm.addIncome(date, amount, walletId, sourceId, desc);
            cout << "Income added successfully!\n";
            break;
        }
            case 2: {
            Date date = inputDate();
            double amount;
            cout << "Enter amount: ";
            cin >> amount;
            mw.showWallets();
            int walletId;
            cout << "Choose wallet ID: ";
            cin >> walletId;
            cm.showCategories();
            int categoryId;
            cout << "Choose category ID: ";
            cin >> categoryId;
            string desc = inputLine("Description: ");
            tm.addExpense(date, amount, walletId, categoryId, desc);
            cout << "Expense added successfully!\n";
            break;
        }
            case 3:
            tm.showIncome(mw, ism);
            break;
            case 4:
            tm.showExpense(mw, cm);
            break;
            case 0:
            cout << "Goodbye!\n";
            break;
            default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 0);
    return 0;
}
