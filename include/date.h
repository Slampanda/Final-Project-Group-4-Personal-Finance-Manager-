#pragma once
#include <fstream>
#include <stdexcept>
#include <iostream>

struct Date{
    int day, month, year;

    Date(int dd = 1, int mm = 1, int yy = 1111);
    bool isLeapYear() const;
    bool isValid() const;
    
    bool operator==(const Date& other) const{
        return day == other.day && month == other.month && year == other.year;
    }
    
    bool operator!=(const Date& other) const{return !(*this == other);}
    
    bool operator<(const Date& other) const{
        if (year != other.year){return year < other.year;}
        if (month != other.month) {return month < other.month;}
        return day < other.day;
    }
    
    bool operator<=(const Date& other) const{return (*this < other) || (*this == other);}
    
    bool operator>(const Date& other) const{return other < *this;}
    
    bool operator>=(const Date& other) const{return !(*this < other);}
    
    int daysBetweeen(const Date& other) const;
    
    void save(std::ofstream& ofs) const;
    void load(std::ifstream& ifs);

    friend std::ostream& operator<<(std::ostream& os, const Date& date);
    friend std::istream& operator>>(std::istream& is, Date& date);
    
    static Date getCurrentDate();
    
private:
    int toDays() const;
};
