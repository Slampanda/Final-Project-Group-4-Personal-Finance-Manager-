#include "expenseCategoryManager.h"
#include <iostream>
#include <fstream>
using namespace std;

CategoryManager :: CategoryManager() : nextCategoryID(1) {}

int CategoryManager :: addCategory(const std::string &name) {
    categories.add(Category(nextCategoryID, name));
    nextCategoryID++;
    return nextCategoryID;
}
string CategoryManager::getCategoryNameFromId (int id) const {
    for(int i=0; i<categories.getSize(); i++) {
        if (categories[i].getId()==id) {
            return categories[i].getName();
        }
    }
    return "Unknown category";
}
void CategoryManager::showCategories() const {
    cout << "========Categories List=========" << endl;
    for (int i=0; i<categories.getSize(); i++) {
        cout << categories[i].getId() << "-" << categories[i].getName();
        cout << endl;
    }
    cout << "================================";
}
void CategoryManager::save(const string &filename) const {
    ofstream ofs(filename.c_str(), ios::binary);
    if (!ofs) return;
    int size = categories.getSize();
    ofs.write((char*)&size, sizeof(size));
    for (int i=0; i<categories.getSize(); i++) {
        categories[i].save(ofs);
    }
    ofs.write((char*)&nextCategoryID, sizeof(nextCategoryID));
}
void CategoryManager::load(const string &filename) {
    ifstream ifs(filename.c_str(), ios::binary);
    if (!ifs) return;
    categories.clear();
    int size = categories.getSize();
    ifs.read((char*)&size, sizeof(size));
    for (int i=0; i<categories.getSize(); i++) {
        Category c;
        c.load(ifs);
        categories.add(c);
    }
    ifs.read((char*)&nextCategoryID, sizeof(size));
}

/*
#include "expenseCategoryManager.h"
#include <iostream>
#include <fstream>
CategoryManager::CategoryManager() : nextCategoryId(1) {}
void CategoryManager::addCategory(const string& name) {
    categories.add(Category(nextCategoryId++, name));
}
string CategoryManager::getCategoryNameById(int id) const {
    for (int i = 0; i < categories.getSize(); i++) {
        if (categories[i].getId() == id)
            return categories[i].getName();
    }
    return "Unknown Category";
}
void CategoryManager::showCategories() const {
    cout << "====== CATEGORIES ======\n";
    for (int i = 0; i < categories.getSize(); i++) {
        cout << categories[i].getId()
             << " - "
             << categories[i].getName() << endl;
    }
}
void CategoryManager::save(const string& filename) const {
    ofstream ofs(filename.c_str(), ios::binary);
    if (!ofs) return;

    int size = categories.getSize();
    ofs.write((char*)&size, sizeof(size));
    ofs.write((char*)&nextCategoryId, sizeof(nextCategoryId));

    for (int i = 0; i < size; i++) {
        categories[i].save(ofs);
    }
}

void CategoryManager::load(const string& filename) {
    ifstream ifs(filename.c_str(), ios::binary);
    if (!ifs) return;

    categories.clear();

    int size;
    ifs.read((char*)&size, sizeof(size));
    ifs.read((char*)&nextCategoryId, sizeof(nextCategoryId));

    for (int i = 0; i < size; i++) {
        Category c;
        c.load(ifs);
        categories.add(c);
    }
}
*/