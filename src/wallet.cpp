#include "wallet.h"

Wallet :: Wallet (
    int id,
    const std::string &name
) : id(id) , name(name) {}

int Wallet::getId() const {
    return id;
}
std::string Wallet::getName() const {
    return name;
}
void Wallet::save(std::ofstream &ofs) const {
    ofs.write((char*)&id, sizeof(id));
    int len = name.size();
    ofs.write((char*)&len, sizeof(len));
    ofs.write(name.c_str(), len);
}
void Wallet::load(std::ifstream &ifs) {
    ifs.read((char*)&id, sizeof(id));
    int len = name.size();
    ifs.read((char*)&name, sizeof(name));
    ifs.read(&name[0], len);
}
