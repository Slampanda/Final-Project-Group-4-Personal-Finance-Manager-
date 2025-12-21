#include "common.h"
#include "incomeSourceManager.h"

SourceManager::SourceManager(const string &nameFile) : namePoolFile("/Users/macair/Downloads/PersonalFinanceManager/PersonalFinanceManager/data/sourceNames.bin"), nextSourceID(1){}

int SourceManager::addSource(const string &name){
    long long nameOffset = addToNamePool(name);
    size_t nameLen = name.length();
        
    IncomeSource newSource(nextSourceID, name, nameLen, nameOffset);
    sources.add(newSource);
    return nextSourceID++;
}

long long SourceManager::addToNamePool(const string &name){
    ofstream ofs(namePoolFile, ios::binary | ios::app);
    if (!ofs){return -1;}
    
    long long offset = ofs.tellp();
    ofs.write(name.c_str(), name.length());
    return offset;
}

string SourceManager::getSourceNameFromId(int id) const{
    for (int i = 0; i<sources.getSize(); i++){
        if (sources[i].getId() == id){
            return sources[i].getName();
        }
    }
    return "Unknown Source";
}

void SourceManager::showSources() const{
    cout << "============= SOURCES LIST ============" << endl;
    for (int i = 0; i<sources.getSize(); i++) {
        cout << sources[i].getId() << " - " << sources[i].getName() << endl;
    }
}

void SourceManager::save(const string &filename) const{
    ofstream ofs(filename, ios::binary);
    if (!ofs){
        cout << "Cannot open Source file to save" << endl;
        return;
    }
    
    // Số lượng sources
    int sourcesCount = sources.getSize();
    ofs.write((char*)&sourcesCount, sizeof(sourcesCount));
    
    // ID cho source tiếp theo
    ofs.write((char*)&nextSourceID, sizeof(nextSourceID));
    
    // Lưu data cho từng source
    for (int i = 0; i<sourcesCount; i++) {
        sources[i].save(ofs);
    }
}

void SourceManager::load(const string &filename) {
    ifstream ifs(filename, ios::binary);
    if (!ifs){
        cout << "Cannot open Source file to load" << endl;
        return;
    }
    
    int sourcesCount;
    ifs.read((char*)&sourcesCount, sizeof(sourcesCount));
    ifs.read((char*)&nextSourceID, sizeof(nextSourceID));
    
    sources.clear();
    
    ifstream nameIfs(namePoolFile, ios::binary);

    for (int i = 0; i<sourcesCount; i++){
        IncomeSource inc;
        inc.load(ifs);
        if (nameIfs){inc.loadName(nameIfs);}
        sources.add(inc);
    }
}

int SourceManager::getSize() const{
    return sources.getSize();
}
