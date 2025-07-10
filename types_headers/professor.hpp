#pragma once
#include <string>

class professor
{
private:
    std::string name;
    std::string surname;
    std::string name_departament;
    int num_departament;

public:
    professor();
    professor(std::string name, std::string surname, int num_departament);
    professor(std::string name, std::string surname, std::string name_departament, int num_departament);
    bool operator==(const professor &other) const;
    bool operator!=(const professor &other) const;
    bool operator<(const professor &other) const;
    bool operator>(const professor &other) const;
    std::string get_name() const;
    std::string get_surname() const;
    std::string get_name_departament() const;
    int get_num_departament() const;
    void set_name(std::string name);
    void set_surname(std::string surname);
    void set_name_departament(std::string name_departament);
    void set_num_departament(int num_departament);
};
