#pragma once
#include "dynamicArray.h"
#include "expenseCategory.h"

class CategoryManager{
private:
    DynamicArray<ExpenseCategory> categories;
    int nextCategoryID = 1;
    std::string namePoolFile;

    long long addToNamePool(const std::string& name);

public:
    CategoryManager(const std::string& nameFile = "data/categoryNames.bin");
    
    int addCategory(const std::string &name);
    std::string getCategoryNameFromId(int id) const;
    void showCategories() const;
    
    void save(const std::string &filename) const;
    void load(const std::string &filename);
    int getSize() const;
};
