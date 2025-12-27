#pragma once
#include <string>
#include <fstream>

class IncomeSource{
private:
    int id;
    std::string name;
    size_t nameLen;
    long long nameOffset;
    
public:
    IncomeSource(int id = 0,
                 const std::string &name = "",
                 size_t nameLen = 0,
                 long long nameOffset = -1
                 );
    
    int getId() const;
    std::string getName() const;
    size_t getNameLen() const;
    long long getNameOffset() const;
    
    void setName(const std::string& newName);
    void setNameLen(size_t newLen);
    void setNameOffset(long long newOffset);
    
    void save(std::ofstream &ofs) const;
    void load(std::ifstream &ifs);
    
    void loadName(std::ifstream &ifs);
};
