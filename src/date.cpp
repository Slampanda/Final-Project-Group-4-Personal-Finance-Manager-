#include "common.h"
#include "date.h"

Date::Date(int dd, int mm, int yy) : day(dd), month(mm), year(yy){
    if (!isValid()){
        throw invalid_argument("Invalid date provided");
    }
}

bool Date::isLeapYear() const{
    if (year%4 == 0) {
        if (year%400 == 0){return true;}
        else if (year%100 == 0){return false;}
        else{return true;}
    }
    return false;
}

bool Date::isValid() const{
    if (month < 1 || month > 12){return false;}
    if (day < 1 || day > 31){return false;}
    if (month == 2){
         return day <= (isLeapYear() ? 29 : 28);
    }
    if (month == 4 || month == 6 || month == 9 || month == 11){return day <= 30;}
    return true;
}

void Date::save(ofstream& ofs) const{
    ofs.write(reinterpret_cast<const char*>(&day), sizeof(day));
    ofs.write(reinterpret_cast<const char*>(&month), sizeof(month));
    ofs.write(reinterpret_cast<const char*>(&year), sizeof(year));
}

void Date::load(ifstream& ifs) {
    ifs.read(reinterpret_cast<char*>(&day), sizeof(day));
    ifs.read(reinterpret_cast<char*>(&month), sizeof(month));
    ifs.read(reinterpret_cast<char*>(&year), sizeof(year));
}

ostream& operator<<(ostream& os, const Date& d) {
    ostream::fmtflags f = os.flags();
    char oldFill = os.fill();

    os << setw(2) << setfill('0') << d.day << "/" << setw(2) << setfill('0') << d.month << "/" << d.year;

    os.flags(f);
    os.fill(oldFill);
    return os;
}

istream& operator>>(istream& is, Date& date) {
    char slash;
    is >> date.day >> slash >> date.month >> slash >> date.year;
    return is;
}

int Date::toDays() const{
    int y = year, m = month, d = day;
    
    m = (m + 9)%12;
    y = y - m/10;
    return 365*y + y/4 - y/100 + y/400 + (m*306 + 5)/10 + (d - 1);
}

int Date::daysBetweeen(const Date& other) const{
    int days1 = this -> toDays();
    int days2 = other.toDays();
    return abs(days1 - days2);
}
