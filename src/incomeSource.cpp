#include "common.h"
#include "incomeSource.h"

IncomeSource::IncomeSource(int id,
                           const string &name,
                           size_t nameLen,
                           long long nameOffset
                           )
: id(id), name(name), nameLen(nameLen), nameOffset(nameOffset){}

int IncomeSource::getId() const {return id;}

string IncomeSource::getName() const{return name;}

size_t IncomeSource::getNameLen() const{return nameLen;}

long long IncomeSource::getNameOffset() const{return nameOffset;}

void IncomeSource::save(ofstream &ofs) const{
    ofs.write((char*)&id, sizeof(id));
    ofs.write((char*)&nameLen, sizeof(nameLen));
    ofs.write((char*)&nameOffset, sizeof(nameOffset));
}

void IncomeSource::load(ifstream &ifs){
    ifs.read((char*)&id, sizeof(id));
    ifs.read((char*)&nameLen, sizeof(nameLen));
    ifs.read((char*)&nameOffset, sizeof(nameOffset));
}

void IncomeSource::loadName(ifstream &ifs){
    if (nameOffset == -1 || nameLen == 0){return;}
    ifs.seekg(nameOffset);
    name.resize(nameLen);
    ifs.read(&name[0], nameLen);
}
