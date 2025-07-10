#pragma once
#include <string>

class student
{
private:
    std::string name;
    std::string surname;
    std::string group_number;
    double grade;

public:
    student();
    student(const std::string &name, double grade);
    student(const std::string &name, const std::string &surname, const std::string &group_number, double grade);
    bool operator==(const student &other) const;
    bool operator!=(const student &other) const;
    bool operator<(const student &other) const;
    bool operator>(const student &other) const;
    std::string get_name() const;
    std::string get_surname() const;
    std::string get_group_number() const;
    double get_grade() const;
    void set_name(const std::string &name);
    void set_surname(const std::string &surname);
    void set_group_number(const std::string &group_number);
    void set_grade(double grade);
};
