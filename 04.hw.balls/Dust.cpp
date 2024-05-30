#include "Dust.hpp"
#include <cmath>


static constexpr double kBallsRadius = 10.0;
static constexpr size_t kBallsCnt = 9;
static constexpr double kBallsVelocity = 500.0;
static constexpr double kBallsLiveTime = 0.2; //Seconds


Dust::Dust(const Point& center, const Color& color):
    create_time_{std::chrono::system_clock::now()},
    balls_{}
{
    for (size_t i = 0; i < kBallsCnt; ++i) {
        Velocity velocity(kBallsVelocity, 2 * M_PI * i / kBallsCnt);
        Ball ball(kBallsRadius, color, false);
        ball.setCenter(center);
        ball.setVelocity(velocity);
        balls_.emplace_back(ball);
    }
}


/**
 * @brief Выполняет отрисовку объекта
 * @param painter контекст отрисовки
 */
void Dust::draw(Painter& painter) const {
    if (!isDead()) {
        for (const Ball& ball: balls_) {
            ball.draw(painter);
        }
    }
}

void Dust::Explosion(const double timePerTick)
{
    if (!isDead()) {
        for (Ball& ball: balls_) {
            ball.move(timePerTick);
        }
    }
}


bool Dust::isDead() const
{
    const auto currentTime = std::chrono::system_clock::now();
    const double delta =
        std::chrono::duration_cast<std::chrono::duration<double>>(currentTime -
                                                                  create_time_)
            .count();
    return delta >= kBallsLiveTime;
}



