#pragma once
#include <iostream>
#include "../types_headers/complex.hpp"
#include "../types_headers/student.hpp"
#include "../types_headers/professor.hpp"

std::istream &operator>>(std::istream &is, student &s);
std::istream &operator>>(std::istream &is, complex &c);
std::istream &operator>>(std::istream &is, professor &p);
std::ostream &operator<<(std::ostream &os, const student &s);
std::ostream &operator<<(std::ostream &os, const complex &c);
std::ostream &operator<<(std::ostream &os, const professor &p);