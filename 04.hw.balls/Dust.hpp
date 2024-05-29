#pragma once
#include <chrono>
#include <vector>
#include "Painter.hpp"
#include "Point.hpp"
#include "Ball.hpp"

class Dust {
public:
    Dust(const Point& center, const Color& color);

    Dust(const Dust&) = default;
    Dust& operator=(Dust&&) = default;

    void draw(Painter& painter) const;
    void Explosion(const double timePerTick);
    bool isLive() const;

private:
    std::chrono::system_clock::time_point create_time_;
    std::vector<Ball> balls_;
};
