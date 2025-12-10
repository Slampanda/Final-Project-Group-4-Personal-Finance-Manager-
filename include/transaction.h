#pragma once
#include "date.h"
#include <string>
using namespace std;

struct Transaction{
    Date date;
    bool isIncome;
    double amount;
    int walletID;
    int referenceID;
    string decription;
    
};

Transaction createTransaction();
void displayTransaction(const Transaction& t);
