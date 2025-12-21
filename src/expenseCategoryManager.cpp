#include "common.h"
#include "expenseCategoryManager.h"

CategoryManager::CategoryManager(const string &nameFile) : namePoolFile("/Users/macair/Downloads/PersonalFinanceManager/PersonalFinanceManager/data/categoryNames.bin"), nextCategoryID(1){}

int CategoryManager::addCategory(const string &name){
    long long nameOffset = addToNamePool(name);
    size_t nameLen = name.length();
        
    ExpenseCategory newCategory(nextCategoryID, name, nameLen, nameOffset);
    categories.add(newCategory);
    return nextCategoryID++;
}

long long CategoryManager::addToNamePool(const string &name){
    ofstream ofs(namePoolFile, ios::binary | ios::app);
    if (!ofs){return -1;}
    
    long long offset = ofs.tellp();
    ofs.write(name.c_str(), name.length());
    return offset;
}

string CategoryManager::getCategoryNameFromId(int id) const{
    for (int i = 0; i<categories.getSize(); i++){
        if (categories[i].getId() == id){
            return categories[i].getName();
        }
    }
    return "Unknown Category";
}

void CategoryManager::showCategories() const{
    cout << "============= CATEGORY LIST ============" << endl;
    for (int i = 0; i<categories.getSize(); i++) {
        cout << categories[i].getId() << " - " << categories[i].getName() << endl;
    }
}

void CategoryManager::save(const string &filename) const{
    ofstream ofs(filename, ios::binary);
    if (!ofs){
        cout << "Cannot open Category file to save" << endl;
        return;
    }
    
    // Số lượng categories
    int categoriesCount = categories.getSize();
    ofs.write((char*)&categoriesCount, sizeof(categoriesCount));
    
    // ID cho category tiếp theo
    ofs.write((char*)&nextCategoryID, sizeof(nextCategoryID));
    
    // Lưu data cho từng source
    for (int i = 0; i<categoriesCount; i++) {
        categories[i].save(ofs);
    }
}

void CategoryManager::load(const string &filename) {
    ifstream ifs(filename, ios::binary);
    if (!ifs){
        cout << "Cannot open Category file to load" << endl;
        return;
    }
    
    int categoriesCount;
    ifs.read((char*)&categoriesCount, sizeof(categoriesCount));
    ifs.read((char*)&nextCategoryID, sizeof(nextCategoryID));
    
    categories.clear();
    
    ifstream nameIfs(namePoolFile, ios::binary);

    for (int i = 0; i<categoriesCount; i++){
        ExpenseCategory exp;
        exp.load(ifs);
        if (nameIfs){exp.loadName(nameIfs);}
        categories.add(exp);
    }
}

int CategoryManager::getSize() const{
    return categories.getSize();
}
