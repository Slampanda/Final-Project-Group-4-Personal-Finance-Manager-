#include "incomeSource.h"

IncomeSource :: IncomeSource (
    int id,
    const std::string &name
) : id(id) , name(name) {}

int IncomeSource::getId() const {
    return id;
}
std::string IncomeSource::getName() const {
    return name;
}
void IncomeSource::save(std::ofstream &ofs) const {
    ofs.write((char*)&id, sizeof(id));
    int len = name.size();
    ofs.write((char*)&len, sizeof(len));
    ofs.write(name.c_str(), len);
}
void IncomeSource::load(std::ifstream &ifs) {
    ifs.read((char*)&id, sizeof(id));
    int len = name.size();
    ifs.read((char*)&name, sizeof(name));
    ifs.read(&name[0], len);
}
