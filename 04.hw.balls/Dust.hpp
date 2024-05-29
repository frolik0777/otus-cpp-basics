#pragma once
#include <chrono>
#include <vector>
#include "Painter.hpp"
#include "Point.hpp"
#include "Ball.hpp"

class Dust {
public:
    Dust(const Point& center, const Color& color);

    void draw(Painter& painter) const;
    void Explosion(const double timePerTick);
    bool isDead() const;

private:
    const std::chrono::system_clock::time_point create_time_;
    std::vector<Ball> balls_;
};
