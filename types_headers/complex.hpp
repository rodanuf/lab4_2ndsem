#pragma once

class complex
{
private:
    double real;
    double imag;

public:
    complex();
    complex(double real);
    complex(double real, double imag);
    complex operator+(const complex &other);
    complex operator-(const complex &other);
    complex operator*(const complex &other);
    complex operator/(const complex &other);
    bool operator==(const complex &other) const;
    bool operator!=(const complex &other) const;
    bool operator<(const complex &other) const;
    bool operator>(const complex &other) const;
    bool operator<=(const complex &other) const;
    bool operator>=(const complex &other) const;
    double get_modulus() const;
    double get_real() const;
    double get_imag() const;
    void set_real(double real);
    void set_imag(double imag);
};
