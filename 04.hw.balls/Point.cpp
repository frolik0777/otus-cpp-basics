#include "Point.hpp"

std::istream& operator>>(std::istream& stream, Point& variable)
{
    stream >> variable.x  >> variable.y;
    return stream;
}