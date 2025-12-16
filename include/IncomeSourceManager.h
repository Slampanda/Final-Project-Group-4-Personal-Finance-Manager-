#pragma once
#include "dynamicArray.h"
#include "incomeSource.h"

class IncomeSourceManager {
private:
    DynamicArray <IncomeSource> sources;
    int nextSourceId = 1;
public:
    IncomeSourceManager();
    int addSource(const std::string &name);
    std::string getSourceNameFromId(int id) const;
    void showSources() const;
    void save (const std::string &filename) const;
    void load (const std::string &filename);
};
/*
#pragma once
#include "DynamicArray.h"
#include "IncomeSource.h"
#include <string>

class IncomeSourceManager {
private:
    DynamicArray<IncomeSource> sources;
    int nextSourceId;

public:
    IncomeSourceManager();

    void addSource(const std::string& name);
    std::string getSourceNameById(int id) const;
    void showSources() const;

    void save(const std::string& filename) const;
    void load(const std::string& filename);
};
*/
