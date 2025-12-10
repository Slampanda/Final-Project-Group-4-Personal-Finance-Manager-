#pragma once
#include <string>

struct IncomeSource{
    int ID;
    string name; //"Lương", "Thưởng", "Học bổng"
};

IncomeSource createIncomeSource();

