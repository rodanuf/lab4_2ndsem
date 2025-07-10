#include <iostream>
#include "../types_headers/student.hpp"

student::student() : name(""), surname(""), group_number(""), grade() {}
student::student(const std::string &name, double grade) : name(name), surname(""), group_number(""), grade(grade) {}
student::student(const std::string &name, const std::string &surname, const std::string &group_number, double grade) : name(name), surname(surname), group_number(group_number), grade(grade) {}

bool student::operator==(const student &other) const
{
    return name == other.name && surname == other.surname && group_number == other.group_number && grade == other.grade;
}

bool student::operator!=(const student &other) const
{
    return name != other.name || surname != other.surname || group_number != other.group_number || grade != other.grade;
}

bool student::operator<(const student &other) const
{
    return grade < other.grade;
}

bool student::operator>(const student &other) const
{
    return grade > other.grade;
}

std::string student::get_name() const
{
    return name;
}

std::string student::get_surname() const
{
    return surname;
}

std::string student::get_group_number() const
{
    return group_number;
}

double student::get_grade() const
{
    return grade;
}

void student::set_name(const std::string &name)
{
    this->name = name;
}

void student::set_surname(const std::string &surname)
{
    this->surname = surname;
}

void student::set_group_number(const std::string &group_number)
{
    this->group_number = group_number;
}

void student::set_grade(double grade)
{
    this->grade = grade;
}
