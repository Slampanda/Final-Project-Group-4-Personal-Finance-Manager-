#include "expenseCategory.h"

Category :: Category (
    int id,
    const std::string &name
) : id(id) , name(name) {}

int Category::getId() const {
    return id;
}
std::string Category::getName() const {
    return name;
}
void Category::save(std::ofstream &ofs) const {
    ofs.write((char*)&id, sizeof(id));
    int len = name.size();
    ofs.write((char*)&len, sizeof(len));
    ofs.write(name.c_str(), len);
}
void Category::load(std::ifstream &ifs) {
    ifs.read((char*)&id, sizeof(id));
    int len = name.size();
    ifs.read((char*)&name, sizeof(name));
    ifs.read(&name[0], len);
}
