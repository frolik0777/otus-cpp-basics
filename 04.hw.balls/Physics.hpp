#pragma once
#include "Ball.hpp"
#include "Dust.hpp"
#include <vector>
#include <deque>

class Physics {
  public:
    Physics(double timePerTick = 0.001);
    void setWorldBox(const Point& topLeft, const Point& bottomRight);
    void update(std::vector<Ball>& balls, std::deque<Dust>& dusts, size_t ticks) const;

  private:
    void collideBalls(std::vector<Ball>& balls, std::deque<Dust>& dusts) const;
    void collideWithBox(std::vector<Ball>& balls) const;
    void animate(std::deque<Dust>& dusts) const;
    void animate(std::vector<Ball>& balls) const;
    void processCollision(Ball& a, Ball& b,
                          double distanceBetweenCenters2) const;
    void createDust(Ball& a, Ball& b, std::deque<Dust>& dusts) const;

  private:
    Point topLeft;
    Point bottomRight;
    double timePerTick;
};
