#include <cmath>
#include "../types_headers/complex.hpp"

complex::complex() : real(0.0), imag(0.0) {}
complex::complex(double real) : real(real), imag(0.0) {}
complex::complex(double real, double imag) : real(real), imag(imag) {}

complex complex::operator+(const complex &other)
{
    return complex(real + other.real, imag + other.imag);
}

complex complex::operator-(const complex &other)
{
    return complex(real - other.real, imag - other.imag);
}

complex complex::operator*(const complex &other)
{
    return complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
}

complex complex::operator/(const complex &other)
{
    double denominator = other.real * other.real + other.imag * other.imag;
    return complex((real * other.real + imag * other.imag) / denominator, (imag * other.real - real * other.imag) / denominator);
}

bool complex::operator==(const complex &other) const
{
    return (real == other.real) && (imag == other.imag);
}

bool complex::operator!=(const complex &other) const
{
    return !(real == other.real) || (imag != other.imag);
}

bool complex::operator<(const complex &other) const
{
    return get_modulus() < other.get_modulus();
}

bool complex::operator>(const complex &other) const
{
    return get_modulus() > other.get_modulus();
}

bool complex::operator<=(const complex &other) const
{
    return get_modulus() <= other.get_modulus();
}

bool complex::operator>=(const complex &other) const
{
    return get_modulus() >= other.get_modulus();
}

double complex::get_modulus() const
{
    return sqrt(real * real + imag * imag);
}

double complex::get_real() const
{
    return real;
}

double complex::get_imag() const
{
    return imag;
}

void complex::set_real(double real)
{
    this->real = real;
}

void complex::set_imag(double imag)
{
    this->imag = imag;
}
