#include "common.h"
#include "expenseCategory.h"

ExpenseCategory::ExpenseCategory(int id,
                                 const string &name,
                                 size_t nameLen,
                                 long long nameOffset
                                 )
: id(id), name(name), nameLen(nameLen), nameOffset(nameOffset){}

int ExpenseCategory::getId() const {return id;}

string ExpenseCategory::getName() const{return name;}

size_t ExpenseCategory::getNameLen() const{return nameLen;}

long long ExpenseCategory::getNameOffset() const{return nameOffset;}

void ExpenseCategory::save(ofstream &ofs) const{
    ofs.write((char*)&id, sizeof(id));
    ofs.write((char*)&nameLen, sizeof(nameLen));
    ofs.write((char*)&nameOffset, sizeof(nameOffset));
}

void ExpenseCategory::load(ifstream &ifs){
    ifs.read((char*)&id, sizeof(id));
    ifs.read((char*)&nameLen, sizeof(nameLen));
    ifs.read((char*)&nameOffset, sizeof(nameOffset));
}

void ExpenseCategory::loadName(ifstream &ifs){
    if (nameOffset == -1 || nameLen == 0){return;}
    ifs.seekg(nameOffset);
    name.resize(nameLen);
    ifs.read(&name[0], nameLen);
}
