#include "IncomeSourceManager.h"
#include <iostream>
#include <fstream>
using namespace std;
IncomeSourceManager::IncomeSourceManager():nextSourceId(1) {
}
int IncomeSourceManager::addSource(const std::string &name) {
    sources.add(IncomeSource(nextSourceId, name));
    return nextSourceId++;
}
std::string IncomeSourceManager::getSourceNameFromId(int id) const {
    for (int i=0; i<sources.getSize(); i++) {
        if (sources[i].getId()==id) {
            return sources[i].getName();
        }
    }
    return "Unknown Source";
}
void IncomeSourceManager::showSources() const {
    cout << "=============Sources List============" << endl;
    for (int i=0; i<sources.getSize(); i++) {
        cout << sources[i].getId() << "-" << sources[i].getName() << endl;
    }
    cout << "=====================================";
}
void IncomeSourceManager::save(const std::string &filename) const {
    ofstream ofs(filename.c_str(), std::ios::binary);
    if (!ofs) return;
    int size = sources.getSize();
    ofs.write((char*)&size, sizeof(size));
    for (int i=0; i<sources.getSize(); i++) {
        sources[i].save(ofs);
    }
    ofs.write((char*)&nextSourceId, sizeof(nextSourceId));
}
void IncomeSourceManager::load(const string &filename) {
    ifstream ifs(filename, std::ios::binary);
    if (!ifs) return;
    sources.clear();
    int size = sources.getSize();
    ifs.read((char*)&size, sizeof(size));
    for (int i=0; i<sources.getSize(); i++) {
        IncomeSource is;
        is.load(ifs);
        sources.add(is);
    }
    ifs.read((char*)&nextSourceId, sizeof(nextSourceId));
}
/*
#include "IncomeSourceManager.h"
#include <iostream>
#include <fstream>
IncomeSourceManager::IncomeSourceManager() : nextSourceId(1) {}
void IncomeSourceManager::addSource(const string& name) {
    sources.add(IncomeSource(nextSourceId++, name));
}
string IncomeSourceManager::getSourceNameById(int id) const {
    for (int i = 0; i < sources.getSize(); i++) {
        if (sources[i].getId() == id)
            return sources[i].getName();
    }
    return "Unknown Source";
}
void IncomeSourceManager::showSources() const {
    cout << "====== INCOME SOURCES ======\n";
    for (int i = 0; i < sources.getSize(); i++) {
        cout << sources[i].getId()
             << " - "
             << sources[i].getName() << endl;
    }
}
void IncomeSourceManager::save(const string& filename) const {
    ofstream ofs(filename.c_str(), ios::binary);
    if (!ofs) return;

    int size = sources.getSize();
    ofs.write((char*)&size, sizeof(size));
    ofs.write((char*)&nextSourceId, sizeof(nextSourceId));

    for (int i = 0; i < size; i++) {
        sources[i].save(ofs);
    }
}
void IncomeSourceManager::load(const string& filename) {
    ifstream ifs(filename.c_str(), ios::binary);
    if (!ifs) return;
    sources.clear();
    int size;
    ifs.read((char*)&size, sizeof(size));
    ifs.read((char*)&nextSourceId, sizeof(nextSourceId));

    for (int i = 0; i < size; i++) {
        IncomeSource s;
        s.load(ifs);
        sources.add(s);
    }
}
*/
