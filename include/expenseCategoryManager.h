#pragma once
#include "dynamicArray.h"
#include "expenseCategory.h"

class CategoryManager {
private:
    DynamicArray<Category> categories;
    int nextCategoryID = 1;
public:
    CategoryManager();
    int addCategory(const std::string &name);
    std::string getCategoryNameFromId(int id) const;
    void showCategories() const;
    void save(const std::string &filename) const;
    void load(const std::string &filename);
};