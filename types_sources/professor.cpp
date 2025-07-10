#include <iostream>
#include "../types_headers/professor.hpp"

professor::professor() : name(""), surname(""), name_departament(""), num_departament(0) {}
professor::professor(std::string name, std::string surname, int num_departament) : name(name), surname(surname), name_departament(""), num_departament(num_departament) {}
professor::professor(std::string name, std::string surname, std::string name_departament, int num_departament) : name(name), surname(surname), name_departament(name_departament), num_departament(num_departament) {}

bool professor::operator==(const professor &other) const
{
    return name == other.name && surname == other.surname && name_departament == other.name_departament && num_departament == other.num_departament;
}

bool professor::operator!=(const professor &other) const
{
    return name != other.name || surname != other.surname || name_departament != other.name_departament || num_departament != other.num_departament;
}

bool professor::operator<(const professor &other) const
{
    return num_departament < other.num_departament;
}

bool professor::operator>(const professor &other) const
{
    return num_departament > other.num_departament;
}

std::string professor::get_name() const
{
    return name;
}

std::string professor::get_surname() const
{
    return surname;
}

std::string professor::get_name_departament() const
{
    return name_departament;
}

int professor::get_num_departament() const
{
    return num_departament;
}

void professor::set_name(std::string name)
{
    this->name = name;
}

void professor::set_surname(std::string surname)
{
    this->surname = surname;
}

void professor::set_name_departament(std::string name_departament)
{
    this->name_departament = name_departament;
}

void professor::set_num_departament(int num_departament)
{
    this->num_departament = num_departament;
}