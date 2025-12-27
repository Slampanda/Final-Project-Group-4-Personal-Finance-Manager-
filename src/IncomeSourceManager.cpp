#include "common.h"
#include "incomeSourceManager.h"

SourceManager::SourceManager(const string &nameFile) : namePoolFile("data/sourceNames.bin"), nextSourceID(1){}

long long SourceManager::calculateNameOffset() const{
    long long currentOffset = 0;
        
    for (int i = 0; i<sources.getSize(); i++){
        const_cast<IncomeSource&>(sources[i]).setNameOffset(currentOffset);
        const_cast<IncomeSource&>(sources[i]).setNameLen(sources[i].getName().length());
            
        currentOffset += sources[i].getNameLen();
    }
    return currentOffset;
}

int SourceManager::addSource(const string &name){
    IncomeSource newSource(nextSourceID, name, name.length(), -1);
    sources.add(newSource);
        
    cout << "Source added (temporary). ID: " << nextSourceID << ", Name: " << name << endl;
        
    return nextSourceID++;
}

string SourceManager::getSourceNameFromId(int id) const{
    for (int i = 0; i<sources.getSize(); i++){
        if (sources[i].getId() == id){
            return sources[i].getName();
        }
    }
    return "Unknown Source";
}

void SourceManager::renameSource(int id, const std::string& newName){
    for (int i = 0; i<sources.getSize(); i++){
        if (sources[i].getId() == id){
            sources[i].setName(newName);
            cout << "✓ Renamed Source " << id << " to: " << newName << endl;
            return;
        }
    }
    cout << "✗ Source ID " << id << " not found!" << endl;
}

void SourceManager::showSources() const{
    cout << "============= SOURCES LIST ============" << endl;
    for (int i = 0; i<sources.getSize(); i++) {
        cout << sources[i].getId() << " - " << sources[i].getName() << endl;
    }
}

int SourceManager::getSize() const{return sources.getSize();}

void SourceManager::save(const string& filename) const{
    const_cast<SourceManager*>(this)->rebuildAndSaveNamePool();

    ofstream ofs(filename.c_str(), ios::binary);
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
    for (int i = 0; i<sourcesCount; i++){
        sources[i].save(ofs);
    }
}

void SourceManager::load(const string& filename){
    ifstream ifs(filename, ios::binary | ios::ate);
    if (!ifs){
        cout << "Cannot open Source file to load" << endl;
        return;
    }
    
    size_t fileSize = ifs.tellg();
    if (fileSize == 0) {
        cout << "Source file is empty" << endl;
        ifs.close();
        return;
    }
    
    ifs.seekg(0, ios::beg);
    
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

void SourceManager::rebuildAndSaveNamePool(){
    cout << "\n=== Rebuilding name pool ===" << endl;
        
    if (sources.getSize() == 0){
        cout << "No sources to save." << endl;
            
        ofstream ofs(namePoolFile, ios::binary | ios::trunc);
        ofs.close();
        return;
    }
        
    // Tính toán offsets và set cho từng source
    long long currentOffset = 0;
    for (int i = 0; i<sources.getSize(); i++){
        size_t nameLen = sources[i].getName().length();
        sources[i].setNameLen(nameLen);
        sources[i].setNameOffset(currentOffset);
        currentOffset += nameLen;
    }
        
    // Ghi toàn bộ tên vào file (truncate mode)
    ofstream ofs(namePoolFile, ios::binary | ios::trunc);
    if (!ofs){
        cout << "Cannot open name pool file!" << endl;
        return;
    }
    
    // Ghi tất cả tên
    for (int i = 0; i<sources.getSize(); i++){
        const string& name = sources[i].getName();
        ofs.write(name.c_str(), name.length());
    }
        
    ofs.close();
    cout << "Name pool saved!" << endl;
}

