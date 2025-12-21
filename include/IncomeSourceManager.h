#pragma once
#include "dynamicArray.h"
#include "incomeSource.h"

class SourceManager{
private:
    DynamicArray<IncomeSource> sources;
    int nextSourceID = 1;
    std::string namePoolFile;
    
    long long addToNamePool(const std::string& name);
    
public:
    SourceManager(const std::string& nameFile = "data/sourceNames.bin");
    
    int addSource(const std::string &name);
    std::string getSourceNameFromId(int id) const;
    void showSources() const;
    
    void save(const std::string &filename) const;
    void load(const std::string &filename);
    int getSize() const;
};
