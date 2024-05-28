#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
public:
    Ball(const double radius, const Color& color, const bool collidable);

    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    bool isCollidable() const;
    void move(const double timePerTick);

private:
    Velocity velocity_{};
    Point center_{};
    const double radius_;
    const double mass_;
    const Color color_;
    const bool collidable_;
};
