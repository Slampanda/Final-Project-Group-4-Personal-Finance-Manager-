#include "common.h"
#include "expenseCategoryManager.h"

CategoryManager::CategoryManager(const string &nameFile) : namePoolFile("data/categoryNames.bin"), nextCategoryID(1){}

long long CategoryManager::calculateNameOffset() const{
    long long currentOffset = 0;
        
    for (int i = 0; i<categories.getSize(); i++){
        const_cast<ExpenseCategory&>(categories[i]).setNameOffset(currentOffset);
        const_cast<ExpenseCategory&>(categories[i]).setNameLen(categories[i].getName().length());
            
        currentOffset += categories[i].getNameLen();
    }
    return currentOffset;
}

int CategoryManager::addCategory(const string &name){
    ExpenseCategory newCategory(nextCategoryID, name, name.length(), -1);
    categories.add(newCategory);
        
    cout << "Category added (temporary). ID: " << nextCategoryID << ", Name: " << name << endl;
        
    return nextCategoryID++;
}

string CategoryManager::getCategoryNameFromId(int id) const{
    for (int i = 0; i<categories.getSize(); i++){
        if (categories[i].getId() == id){
            return categories[i].getName();
        }
    }
    return "Unknown Category";
}

void CategoryManager::renameCategory(int id, const std::string& newName){
    for (int i = 0; i<categories.getSize(); i++){
        if (categories[i].getId() == id){
            categories[i].setName(newName);
            cout << "✓ Renamed Category " << id << " to: " << newName << endl;
            return;
        }
    }
    cout << "✗ Category ID " << id << " not found!" << endl;
}

void CategoryManager::showCategories() const{
    cout << "============= CATEGORIES LIST ============" << endl;
    for (int i = 0; i<categories.getSize(); i++) {
        cout << categories[i].getId() << " - " << categories[i].getName() << endl;
    }
}

int CategoryManager::getSize() const{return categories.getSize();}

void CategoryManager::save(const string& filename) const{
    const_cast<CategoryManager*>(this)->rebuildAndSaveNamePool();

    ofstream ofs(filename.c_str(), ios::binary);
    if (!ofs){
        cout << "Cannot open Category file to save" << endl;
        return;
    }
    
    // Số lượng categories
    int categoriesCount = categories.getSize();
    ofs.write((char*)&categoriesCount, sizeof(categoriesCount));
    
    // ID cho category tiếp theo
    ofs.write((char*)&nextCategoryID, sizeof(nextCategoryID));
    
    // Lưu data cho từng category
    for (int i = 0; i<categoriesCount; i++){
        categories[i].save(ofs);
    }
}

void CategoryManager::load(const string& filename){
    ifstream ifs(filename, ios::binary | ios::ate);
    if (!ifs){
        cout << "Cannot open Category file to load" << endl;
        return;
    }
    
    size_t fileSize = ifs.tellg();
    if (fileSize == 0) {
        cout << "Category file is empty" << endl;
        ifs.close();
        return;
    }
    
    ifs.seekg(0, ios::beg);
    
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

void CategoryManager::rebuildAndSaveNamePool(){
    cout << "\n=== Rebuilding name pool ===" << endl;
        
    if (categories.getSize() == 0){
        cout << "No categories to save." << endl;
            
        ofstream ofs(namePoolFile, ios::binary | ios::trunc);
        ofs.close();
        return;
    }
        
    // Tính toán offsets và set cho từng category
    long long currentOffset = 0;
    for (int i = 0; i<categories.getSize(); i++){
        size_t nameLen = categories[i].getName().length();
        categories[i].setNameLen(nameLen);
        categories[i].setNameOffset(currentOffset);
        currentOffset += nameLen;
    }
        
    // Ghi toàn bộ tên vào file (truncate mode)
    ofstream ofs(namePoolFile, ios::binary | ios::trunc);
    if (!ofs){
        cout << "Cannot open name pool file!" << endl;
        return;
    }
    
    // Ghi tất cả tên
    for (int i = 0; i<categories.getSize(); i++){
        const string& name = categories[i].getName();
        ofs.write(name.c_str(), name.length());
    }
        
    ofs.close();
    cout << "Name pool saved!" << endl;
}

