#include "common.h"
#include "financeManager.h"
#include "numberUtils.h"

FinanceManager::FinanceManager() : walletManager(WALLET_NAME_FILE),
                                   sourceManager(SOURCE_NAME_FILE),
                                   categoryManager(CATEGORY_NAME_FILE)
                                   {
    loadAllData();
    // Kiểm tra không có dữ liệu thì tự tạo mẫu
    if (walletManager.getSize() == 0){
        initializeSampleData();
    }
    processRecurringTransactions();
}


// Core method
void FinanceManager::loadAllData(){
    walletManager.load(WALLET_FILE);
    sourceManager.load(SOURCE_FILE);
    categoryManager.load(CATEGORY_FILE);
    transactionManager.load(TRANSACTION_FILE);
    
    // Load recurring transactions
    ifstream ifs(RECURRING_FILE, ios::binary);
    if (ifs){
        int size;
        ifs.read(reinterpret_cast<char*>(&size), sizeof(size));
        ifs.read(reinterpret_cast<char*>(&nextRecurringId), sizeof(nextRecurringId));
        
        recurringTransactions.clear();
        for (int i = 0; i<size; i++){
            RecurringTransaction rt;
            rt.load(ifs);
            recurringTransactions.add(rt);
        }
    }
}

void FinanceManager::saveAllData() const{
    walletManager.save(WALLET_FILE);
    sourceManager.save(SOURCE_FILE);
    categoryManager.save(CATEGORY_FILE);
    transactionManager.save(TRANSACTION_FILE);
    
    // Save recurring transactions
    ofstream ofs(RECURRING_FILE, ios::binary);
    if (ofs){
        int size = recurringTransactions.getSize();
        ofs.write(reinterpret_cast<const char*>(&size), sizeof(size));
        ofs.write(reinterpret_cast<const char*>(&nextRecurringId), sizeof(nextRecurringId));
        
        for (int i = 0; i<size; i++){
            recurringTransactions[i].save(ofs);
        }
    }
}

void FinanceManager::processRecurringTransactions(){
    Date currentDate;
    // Giả sử currentDate là ngày hiện tại
    // Trong thực tế: currentDate = Date::getCurrentDate();
    
    // Đơn giản: dùng ngày 1/1/2024 cho demo
    currentDate = Date(1, 1, 2024);
    
    for (int i = 0; i<recurringTransactions.getSize(); i++){
        if (recurringTransactions[i].shouldProcess(currentDate)){
            
            // Tạo income transaction
            if (recurringTransactions[i].getIsIncome()){
                transactionManager.addIncome(currentDate,
                                             recurringTransactions[i].getAmount(),
                                             recurringTransactions[i].getWalletID(),
                                             recurringTransactions[i].getSourceCategoryID(),
                                             recurringTransactions[i].getDescription()
                                             );
            
                // UPDATE WALLET BALANCE
                walletManager.updateWalletBalance(recurringTransactions[i].getWalletID(),
                                                  recurringTransactions[i].getAmount(),
                                                  true
                                                  );
            }
            // Tạo expense transaction
            else{
                transactionManager.addExpense(currentDate,
                                              recurringTransactions[i].getAmount(),
                                              recurringTransactions[i].getWalletID(),
                                              recurringTransactions[i].getSourceCategoryID(),
                                              recurringTransactions[i].getDescription()
                                              );
                // UPDATE WALLET BALANCE
                walletManager.updateWalletBalance(recurringTransactions[i].getWalletID(),
                                                  recurringTransactions[i].getAmount(),
                                                  false
                                                  );
            }
                
            // Cập nhật lastProcessed
            recurringTransactions[i].setLastProcessed(currentDate);
            cout << "Processed recurring transaction ID: " << recurringTransactions[i].getID() << endl;
        }
    }
}

// Dashboard
void FinanceManager::showDashboard() const{
    cout << "\n========== DASHBOARD ==========" << endl;
    
    // Hiển thị Wallets
    walletManager.showWallets();
    
    // Tính tổng số dư
    double totalBalance = walletManager.getTotalBalance();
    
    cout << "-------------------" << endl;
    cout << "TOTAL BALANCE: " << formatNumber(totalBalance) << endl;
    
    // Tính income/expense tháng này
    Date today; // Ngày hiện tại
    Date firstOfMonth(1, today.month, today.year); // Ngày đầu tháng
    double monthlyIncome = transactionManager.getTotalIncomeBetween(firstOfMonth, today);
    double monthlyExpense = transactionManager.getTotalExpenseBetween(firstOfMonth, today);
    double monthlyNet = monthlyIncome - monthlyExpense;
    
    cout << "\nTHIS MONTH:" << endl;
    cout << "Income: " << monthlyIncome << endl;
    cout << "Expense: " << monthlyExpense << endl;
    cout << "Net: " << monthlyNet << endl;
    cout << "==============================" << endl;
}

// Statistics
void FinanceManager::showStatistics(){
    int choice;
    do {
        cout << "\n=========== STATISTICS & REPORTS ===========" << endl;
        cout << "1. Time-based Statistics (Custom Date Range)" << endl;
        cout << "2. Wallet-based Statistics" << endl;
        cout << "3. Yearly Overview" << endl;
        cout << "4. Income Breakdown by Source" << endl;
        cout << "5. Expense Breakdown by Category" << endl;
        cout << "6. Net Balance Report" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "===========================================" << endl;
        cout << "Your choice: ";
        cin >> choice;
        
        switch (choice){
            case 1:{
                Date start = inputDate("Enter start date (dd mm yyyy): ");
                Date end = inputDate("Enter end date (dd mm yyyy): ");
                showTimeBasedStats(start, end);
                break;
            }
            case 2:{
                int walletId = selectWallet();
                Date start = inputDate("Enter start date (dd mm yyyy): ");
                Date end = inputDate("Enter end date (dd mm yyyy): ");
                showWalletStats(walletId, start, end);
                break;
            }
            case 3:{
                int year;
                cout << "Enter year: ";
                cin >> year;
                showYearlyStats(year);
                break;
            }
            case 4:{
                Date start = inputDate("Enter start date (dd mm yyyy): ");
                Date end = inputDate("Enter end date (dd mm yyyy): ");
                showIncomeBreakdown(start, end);
                break;
            }
            case 5:{
                Date start = inputDate("Enter start date (dd mm yyyy): ");
                Date end = inputDate("Enter end date (dd mm yyyy): ");
                showExpenseBreakdown(start, end);
                break;
            }
            case 6:{
                Date start = inputDate("Enter start date (dd mm yyyy): ");
                Date end = inputDate("Enter end date (dd mm yyyy): ");
                showNetBalanceReport(start, end);
                break;
            }
            case 0:{
                return;
            }
        }
    } while (choice != 0);
}

void FinanceManager::showTimeBasedStats(const Date& start, const Date& end) const {
    cout << "\n====== TIME-BASED STATISTICS ======" << endl;
    cout << "Period: " << start << " to " << end << endl;
    
    double income = transactionManager.getTotalIncomeBetween(start, end);
    double expense = transactionManager.getTotalExpenseBetween(start, end);
    double net = income - expense;
    
    cout << fixed << setprecision(2);
    cout << "Total income: " << income << endl;
    cout << "Total expense: " << expense << endl;
    cout << "Net balance: " << net << endl;
    
    int days = start.daysBetweeen(end) + 1;
    cout << "Days in period: " << days << endl;
    
    if (days > 0){
        cout << "Average Daily Income: " << (income / days) << endl;
        cout << "Average Daily Expense: " << (expense / days) << endl;
        cout << "Average Daily Net: " << (net / days) << endl;
    }
    
    if (income > 0){
        double expenseRatio = (expense / income) * 100;
        cout << "Expense/Income Ratio: " << expenseRatio << "%" << endl;
    }
}

void FinanceManager::showYearlyStats(int year) const{
    Date start(1, 1, year);
    Date end(31, 12, year);
    showTimeBasedStats(start, end);
}

void FinanceManager::showWalletStats(int walletID, const Date& start, const Date& end) const{
    cout << "\n====== WALLET STATISTICS ======" << endl;
    
    string walletName = walletManager.getWalletNameFromId(walletID);
    cout << "Wallet: " << walletName << " (ID: " << walletID << ")" << endl;
    cout << "Period: " << start << " to " << end << endl;
    
    double income = transactionManager.getWalletIncomeBetween(walletID, start, end);
    double expense = transactionManager.getWalletExpenseBetween(walletID, start, end);
    double net = income - expense;
    
    cout << fixed << setprecision(2);
    cout << "Income: " << income << endl;
    cout << "Expense: " << expense << endl;
    cout << "Net: " << net << endl;
    
    // Hiển thị balance hiện tại
    double currentBalance = walletManager.getWalletBalance(walletID);
    cout << "Current Balance: " << currentBalance << endl;
}

void FinanceManager::showIncomeBreakdown(const Date& start, const Date& end) const{
    cout << "\n====== INCOME BREAKDOWN BY SOURCE ======" << endl;
    cout << "Period: " << start << " to " << end << endl;
        
    auto incomeBySource = transactionManager.getIncomeBySource(start, end);
    double totalIncome = 0;
    
    for (int i = 0; i<incomeBySource.getSize(); i++){
        int sourceID = incomeBySource[i].first;
        double amount = incomeBySource[i].second;
        string sourceName = sourceManager.getSourceNameFromId(sourceID);
        
        cout << sourceName << ": " << fixed << setprecision(2) << amount << endl;
        totalIncome += amount;
    }
    
    cout << "----------------------" << endl;
    cout << "Total Income: " << totalIncome << endl;
}

void FinanceManager::showExpenseBreakdown(const Date& start, const Date& end) const{
    cout << "\n====== EXPENSE BREAKDOWN BY CATEGORY ======" << endl;
    cout << "Period: " << start << " to " << end << endl;
        
    auto expenseByCategory = transactionManager.getExpenseByCategory(start, end);
    double totalExpense = 0;
    
    for (int i = 0; i<expenseByCategory.getSize(); i++){
        int categoryID = expenseByCategory[i].first;
        double amount = expenseByCategory[i].second;
        string categoryName = categoryManager.getCategoryNameFromId(categoryID);
        
        cout << categoryName << ": " << fixed << setprecision(2) << amount << endl;
        totalExpense += amount;
    }
    
    cout << "----------------------" << endl;
    cout << "Total Expense: " << totalExpense << endl;
}

void FinanceManager::showNetBalanceReport(const Date& start, const Date& end) const{
    showTimeBasedStats(start, end);
}

// Menu handlers

void FinanceManager::handleAddIncome(){
    cout << "\n==== ADD INCOME TRANSACTION ====" << endl;
    Date date = inputDate("Enter date (dd mm yyyy): ");
    double amount = inputAmount("Enter amount: ");
    int walletId = selectWallet();
    int sourceId = selectIncomeSource();
    string desc = inputLine("Description (optional): ");
    
    // Gọi transactionManager.addIncome
    transactionManager.addIncome(date, amount, walletId, sourceId, desc);
    // Cập nhật wallet balance
    walletManager.updateWalletBalance(walletId, amount, true);
    cout << "Income added successfully!" << endl;
}

void FinanceManager::handleAddExpense(){
    cout << "\n==== ADD EXPENSE TRANSACTION ====" << endl;
    Date date = inputDate("Enter date (dd mm yyyy): ");
    double amount = inputAmount("Enter amount: ");
    int walletId = selectWallet();
    
    // Kiểm tra balance
    double balance = walletManager.getWalletBalance(walletId);
        if (balance < amount){
            cout << "Error: Not enough balance in wallet!\n";
            return;
        }
        
        int categoryId = selectExpenseCategory();
        string desc = inputLine("Description (optional): ");
    
    // Gọi transactionManager.addExpense
    transactionManager.addExpense(date, amount, walletId, categoryId, desc);
        
    // Cập nhật wallet balance
    walletManager.updateWalletBalance(walletId, amount, false);
        
    cout << "Expense added successfully!" << endl;
}

void FinanceManager::handleAddRecurring(){
    cout << "\n==== ADD RECURRING TRANSACTION ====" << endl;
    
    bool isIncome;
    cout << "Is this income? (1 = Yes, 0 = No): ";
    cin >> isIncome;
    
    double amount = inputAmount("Enter amount: ");
    int walletId = selectWallet();
    
    int sourceCategoryId;
    if (isIncome){sourceCategoryId = selectIncomeSource();}
    
    else{sourceCategoryId = selectExpenseCategory();}
    
    string desc = inputLine("Description (optional): ");
    Date startDate = inputDate("Start date (dd mm yyyy): ");
    
    char hasEndDate;
    cout << "Has end date? (y/n): ";
    cin >> hasEndDate;
    
    Date endDate(0, 0, 0);
    if (hasEndDate == 'y' || hasEndDate == 'Y') {
        endDate = inputDate("End date (dd mm yyyy): ");
    }
    
    RecurringTransaction rt(nextRecurringId++, isIncome, amount, walletId, sourceCategoryId, desc, startDate, endDate);
    recurringTransactions.add(rt);
    
    cout << "Recurring transaction added successfully! ID: " << rt.getID() << endl;
}

void FinanceManager::handleViewAllTransactions(){
    cout << "\n==== VIEW ALL TRANSACTIONS ====" << endl;
    // Gọi phương thức từ transactionManager
    transactionManager.showAllTransactions(walletManager, sourceManager, categoryManager);
}

void FinanceManager::handleManageWallets(){
    int choice;
    do{
        cout << "\n==== MANAGE WALLETS ====" << endl;
        cout << "1. View All Wallets" << endl;
        cout << "2. Add New Wallet" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Your choice: ";
        cin >> choice;
        
        switch (choice){
            case 1:{
                walletManager.showWallets();
                break;
            }
                
            case 2:{
                string name;
                double balance;
                cout << "Enter wallet name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter initial balance: ";
                cin >> balance;
                int id = walletManager.addWallet(name, balance);
                cout << "Wallet added with ID: " << id << endl;
                break;
            }
            case 0:
                return;
        }
    } while (choice != 0);
}

void FinanceManager::handleManageSources(){
    int choice;
        do{
            cout << "\n==== MANAGE INCOME SOURCES ====" << endl;
            cout << "1. View All Sources" << endl;
            cout << "2. Add New Source" << endl;
            cout << "0. Back to Main Menu" << endl;
            cout << "Your choice: ";
            cin >> choice;
            
            switch (choice){
                case 1:{
                    sourceManager.showSources();
                    break;
                }
                    
                case 2:{
                    string name;
                    cout << "Enter source name: ";
                    cin.ignore();
                    getline(cin, name);
                    if (!name.empty()) {
                        int id = sourceManager.addSource(name);
                        cout << "Source added with ID: " << id << endl;
                    }
                    break;
                }
                case 0:
                    return;
            }
        } while (choice != 0);
}

void FinanceManager::handleManageCategories(){
    int choice;
        do{
            cout << "\n==== MANAGE EXPENSE CATEGORIES ====" << endl;
            cout << "1. View All Categories" << endl;
            cout << "2. Add New Category" << endl;
            cout << "0. Back to Main Menu" << endl;
            cout << "Your choice: ";
            cin >> choice;
            
            switch (choice){
                case 1:{
                    categoryManager.showCategories();
                    break;
                }
                case 2:{
                    string name;
                    cout << "Enter category name: ";
                    cin.ignore();
                    getline(cin, name);
                    if (!name.empty()) {
                        int id = categoryManager.addCategory(name);
                        cout << "Category added with ID: " << id << endl;
                    }
                    break;
                }
                case 0:
                    return;
            }
        } while (choice != 0);
}
// Các method khác tương tự...

// Menu handlers


void FinanceManager::run(){
    int choice;
    do {
        cout << "\n=========== PERSONAL FINANCE MANAGER ===========" << endl;
        cout << "1. Dashboard" << endl;
        cout << "2. Add Income Transaction" << endl;
        cout << "3. Add Expense Transaction" << endl;
        cout << "4. Add Recurring Transaction" << endl;
        cout << "5. View All Transactions" << endl;
        cout << "6. Statistics & Reports" << endl;
        cout << "7. Manage Wallets" << endl;
        cout << "8. Manage Income Sources" << endl;
        cout << "9. Manage Expense Categories" << endl;
        cout << "10. Process Recurring Transactions" << endl;
        cout << "0. Exit" << endl;
        cout << "================================================" << endl;
        cout << "Your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: showDashboard(); break;
            case 2: handleAddIncome(); break;
            case 3: handleAddExpense(); break;
            case 4: handleAddRecurring(); break;
            case 5: handleViewAllTransactions(); break;
            case 6: showStatistics(); break;
            case 7: handleManageWallets(); break;
            case 8: handleManageSources(); break;
            case 9: handleManageCategories(); break;
            case 10:{
                processRecurringTransactions();
                cout << "Recurring transactions process." << endl;
                break;
            }
            case 0:{
                saveAllData();
                cout << "Data saved. Goodbye!" << endl;
                break;
            }
            default:{
                cout << "Invalid choice!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    } while (choice != 0);
}

// Helper methods
Date FinanceManager::inputDate(const string& prompt) const{
    int d, m, y;
    while (true){
        cout << prompt;
        cin >> d >> m >> y;
        try{
            return Date(d, m, y);
        } catch (...) {
            cout << "Invalid date! Try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

string FinanceManager::inputLine(const string& prompt) const{
    cout << prompt;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string s;
    getline(cin, s);
    return s;
}

double FinanceManager::inputAmount(const string& prompt) const{
    double amount;
    while (true){
        cout << prompt;
        cin >> amount;
        if (cin.fail() || amount < 0){
            cout << "Invalid amount! Enter a positive number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else{break;}
    }
    return amount;
}

int FinanceManager::selectWallet(){
    int id;
    while (true){
        walletManager.showWallets();
        cout << "\nSelect wallet ID (or 0 to add new): ";
        cin >> id;
        
        // Thêm wallet mới
        if (id == 0){
            string newName;
            cout << "Enter new wallet name: ";
            cin.ignore();
            getline(cin, newName);
            
            if (!newName.empty()){
                int newId = walletManager.addWallet(newName);
                cout << "New wallet '" << newName << "' added with ID: " << newId << endl;
                return newId;
            }
            
            else{cout << "Wallet name cannot be empty!" << endl;}
        }
        
        else{
            // Kiểm tra ID có tồn tại không
            string walletName = walletManager.getWalletNameFromId(id);
            // ID đã tồn tại
            if (walletName != "Unknown Wallet"){return id;}
            
            //ID không tồn tại
            else{
                cout << "\nWallet ID " << id << " does not exist!" << endl;
                cout << "What would you like to do?" << endl;
                cout << "1. Try another ID" << endl;
                cout << "2. Add new wallet with this ID" << endl;
                cout << "3. Cancel and go back to menu" << endl;
                cout << "Your choice: ";
                
                int choice; cin >> choice;
                
                // choice == 1 -> loop
                if (choice == 2){
                    string newName;
                    cout << "Enter new wallet name: ";
                    cin.ignore();
                    getline(cin, newName);
                    
                    if (!newName.empty()){
                        int newId = walletManager.addWallet(newName);
                        cout << "New wallet '" << newName << "' added with ID: " << newId << endl;
                        return newId;
                    }
                    else{cout << "Wallet name cannot be empty!" << endl;}
                }
                else if (choice == 3){
                    throw runtime_error("Operation cancelled by user");
                }
            }
        }
    }
}

int FinanceManager::selectIncomeSource(){
    int id;
    while (true){
        sourceManager.showSources();
        cout << "\nSelect source ID (or 0 to add new): ";
        cin >> id;
        
        // Thêm source mới
        if (id == 0){
            string newName;
            cout << "Enter new source name: ";
            cin.ignore();
            getline(cin, newName);
            
            if (!newName.empty()){
                int newId = sourceManager.addSource(newName);
                cout << "New source '" << newName << "' added with ID: " << newId << endl;
                return newId;
            }
            
            else{cout << "Source name cannot be empty!" << endl;}
        }
        
        else{
            // Kiểm tra ID có tồn tại không
            string sourceName = sourceManager.getSourceNameFromId(id);
            // ID đã tồn tại
            if (sourceName != "Unknown Source"){return id;}
            
            //ID không tồn tại
            else{
                cout << "\nSource ID " << id << " does not exist!" << endl;
                cout << "What would you like to do?" << endl;
                cout << "1. Try another ID" << endl;
                cout << "2. Add new source with this ID" << endl;
                cout << "3. Cancel and go back to menu" << endl;
                cout << "Your choice: ";
                
                int choice; cin >> choice;
                
                // choice == 1 -> loop
                if (choice == 2){
                    string newName;
                    cout << "Enter new source name: ";
                    cin.ignore();
                    getline(cin, newName);
                    
                    if (!newName.empty()){
                        int newId = sourceManager.addSource(newName);
                        cout << "New source '" << newName << "' added with ID: " << newId << endl;
                        return newId;
                    }
                    else{cout << "Source name cannot be empty!" << endl;}
                }
                else if (choice == 3){
                    throw runtime_error("Operation cancelled by user");
                }
            }
        }
    }
}

int FinanceManager::selectExpenseCategory(){
    int id;
    while (true){
        categoryManager.showCategories();
        cout << "\nSelect category ID (or 0 to add new): ";
        cin >> id;
        
        // Thêm category mới
        if (id == 0){
            string newName;
            cout << "Enter new category name: ";
            cin.ignore();
            getline(cin, newName);
            
            if (!newName.empty()){
                int newId = categoryManager.addCategory(newName);
                cout << "New category '" << newName << "' added with ID: " << newId << endl;
                return newId;
            }
            
            else{cout << "Category name cannot be empty!" << endl;}
        }
        
        else{
            // Kiểm tra ID có tồn tại không
            string categoryName = categoryManager.getCategoryNameFromId(id);
            // ID đã tồn tại
            if (categoryName != "Unknown Category"){return id;}
            
            //ID không tồn tại
            else{
                cout << "\nCategory ID " << id << " does not exist!" << endl;
                cout << "What would you like to do?" << endl;
                cout << "1. Try another ID" << endl;
                cout << "2. Add new category with this ID" << endl;
                cout << "3. Cancel and go back to menu" << endl;
                cout << "Your choice: ";
                
                int choice; cin >> choice;
                
                // choice == 1 -> loop
                if (choice == 2){
                    string newName;
                    cout << "Enter new category name: ";
                    cin.ignore();
                    getline(cin, newName);
                    
                    if (!newName.empty()){
                        int newId = categoryManager.addCategory(newName);
                        cout << "New category '" << newName << "' added with ID: " << newId << endl;
                        return newId;
                    }
                    else{cout << "Category name cannot be empty!" << endl;}
                }
                else if (choice == 3){
                    throw runtime_error("Operation cancelled by user");
                }
            }
        }
    }
}

void FinanceManager::initializeSampleData() {
    // Tạo dữ liệu mẫu nếu không có file
    walletManager.addWallet("Cash", 0.0);
    walletManager.addWallet("Bank", 0.0);
    walletManager.addWallet("Momo", 0.0);
    
    sourceManager.addSource("Salary");
    sourceManager.addSource("Bonus");
    sourceManager.addSource("Investment");
    
    categoryManager.addCategory("Food");
    categoryManager.addCategory("Transportation");
    categoryManager.addCategory("Shopping");
    categoryManager.addCategory("Entertainment");
}
