#pragma once
#include <string>
#include <fstream>

class Wallet {
private:
    int id;
    std::string name;
    double balance;
    size_t nameLen;
    long long nameOffset;
    
public:
    Wallet(int id = 0,
           const std::string &name = "",
           double balance = 0.0,
           size_t nameLen = 0,
           long long nameOffset = -1
           );
    
    int getId() const;
    std::string getName() const;
    double getBalance() const;
    size_t getNameLen() const;
    long long getNameOffset() const;
    
    void setName(const std::string& newName);
    void setBalance(double newBalance);
    void setNameLen(size_t newLen);
    void setNameOffset(long long newOffset);
    
    // Chỉ lưu fixed-size data: walletID, balance, nameLen, nameOffset
    void save(std::ofstream &ofs) const;
    void load(std::ifstream &ifs);
    
    // Lưu và hiển thị Name
    void loadName(std::ifstream &ifs);
};
