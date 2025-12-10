#include "date.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

string changeFormat(Date d);

Date inputDate(){
    Date d;
    cin >> d.day >> d.month >> d.year;
    return d;
}

string changeFormat(Date d){
    stringstream ss;
    ss << setw(2) << setfill('0') << d.day << "/"
       << setw(2) << setfill('0') << d.month << "/"
       << setw(4) << setfill('0') << d.year;
    return ss.str();
}
