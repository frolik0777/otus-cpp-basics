#include "Color.hpp"

Color::Color() = default;

Color::Color(double red, double green, double blue)
    : r{red}, g{green}, b{blue} {}

double Color::red() const {
    return r;
}

double Color::green() const {
    return g;
}

double Color::blue() const {
    return b;
}

std::istream& operator>>(std::istream& stream, Color& variable)
{
    double r;
    double g;
    double b;
    stream >> r >> g >> b;
    variable = Color(r, g, b);
    return stream;
}