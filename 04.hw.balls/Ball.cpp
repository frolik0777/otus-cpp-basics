#include "Ball.hpp"
#include <cmath>


Ball::Ball(const double radius, const Color& color, const bool collidable):
    radius_{radius},
    mass_{M_PI * radius_ * radius_ * radius_ * 4.0 / 3.0},
    color_{color},
    collidable_{collidable}
{

}

/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Ball::setVelocity(const Velocity& velocity) {
    velocity_ = velocity;
}

/**
 * @return скорость объекта
 */
Velocity Ball::getVelocity() const {
    return velocity_;
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter& painter) const {
    painter.draw(center_, radius_, color_);
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter(const Point& center) {
    center_ = center;
}

/**
 * @return центр объекта
 */
Point Ball::getCenter() const {
    return center_;
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Ball::getRadius() const {
    return radius_;
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
double Ball::getMass() const {
    return mass_;
}

/**
 * @brief Возвращает флаг коллизий
 * @details В нашем приложении шары, которые имеют
 * isCollidable==falsee, не сталкиваются с другими объектами,
 * и проходят сквозь них
 */
bool Ball::isCollidable() const
{
    return collidable_;
}

void Ball::move(const double timePerTick) {
        Point newPos =
            getCenter() + getVelocity().vector() * timePerTick;
        setCenter(newPos);
}