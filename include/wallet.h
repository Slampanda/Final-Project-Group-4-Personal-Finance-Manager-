#pragma once
#include <string>
#include <fstream>

class Wallet {
private:
    int id;
    std::string name;
public:
    Wallet(
        int id = 0,
        const std::string &name = ""
    );
    int getId() const;
    std::string getName() const;
    void save(std::ofstream &ofs) const;
    void load(std::ifstream &ifs);
};