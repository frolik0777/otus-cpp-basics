#include "Velocity.hpp"

std::istream& operator>>(std::istream& stream, Velocity& variable) {
    Point p;
    stream >> p;
    variable.setVector(p);
    return stream;
}