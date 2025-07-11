#include "../ui_headers/io_functions.hpp"

std::istream &operator>>(std::istream &is, student &s)
{
    std::string name, surname, group_number;
    float grade;
    is >> name >> surname >> group_number >> grade;
    if (grade < 0 || grade > 5.0)
    {
        is.setstate(std::ios::failbit);
    }
    s.set_name(name);
    s.set_surname(surname);
    s.set_group_number(group_number);
    s.set_grade(grade);
    return is;
}

std::istream &operator>>(std::istream &is, complex &c)
{
    double real = 0.0;
    double imag = 0.0;
    char next_symbol;
    is >> real;
    while (is.peek() == ' ')
    {
        is.get();
    }
    next_symbol = is.peek();
    if (next_symbol == 'i')
    {
        c.set_real(0.0);
        c.set_imag(real);
        return is;
    }
    if (next_symbol == '+' || next_symbol == '-')
    {
        char operators, i;
        is >> operators;
        while (is.peek() == ' ')
        {
            is.get();
        }
        is >> imag;
        while (is.peek() == ' ')
        {
            is.get();
        }
        is >> i;
        if (i != 'i')
        {
            is.setstate(std::ios::failbit);
            return is;
        }
    }
    c.set_real(real);
    c.set_imag(imag);
    return is;
}

std::istream &operator>>(std::istream &is, professor &p)
{
    std::string name, surname, name_departament;
    int num_departament;
    is >> name >> surname >> name_departament >> num_departament;
    p.set_name(name);
    p.set_surname(surname);
    p.set_name_departament(name_departament);
    p.set_num_departament(num_departament);
    return is;
}

std::ostream &operator<<(std::ostream &os, const student &s)
{
    os << s.get_name() << " " << s.get_surname() << " " << s.get_group_number() << " " << s.get_grade();
    return os;
}

std::ostream &operator<<(std::ostream &os, const complex &c)
{
    if (c.get_imag() < 0 && c.get_imag() != -1)
    {
        os << c.get_real() << c.get_imag() << "i";
    }
    else if (c.get_imag() == -1)
    {
        os << c.get_real() << "-i";
    }
    else if (c.get_imag() == 0)
    {
        os << c.get_real();
    }
    else
    {
        os << c.get_real() << " + " << c.get_imag() << "i";
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const professor &p)
{
    os << p.get_name() << " " << p.get_surname() << " " << p.get_name_departament() << " " << p.get_num_departament();
    return os;
}