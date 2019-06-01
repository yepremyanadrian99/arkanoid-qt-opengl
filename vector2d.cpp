#include "vector2d.h"

Vector2D::Vector2D()
    :x(0), y(0) {
}

Vector2D::Vector2D(qreal x, qreal y)
    :x(x), y(y) {
}

qreal Vector2D::getX() const {
    return this->x;
}

void Vector2D::setX(qreal x) {
    this->x = x;
}

qreal Vector2D::getY() const {
    return this->y;
}

void Vector2D::setY(qreal y) {
    this->y = y;
}

void Vector2D::reverseX() {
    this->x = -x;
}

void Vector2D::reverseY() {
    this->y = -y;
}

qreal Vector2D::length() const {
    return std::sqrt(this->x * this->x + this->y * this->y);
}

void Vector2D::rotate(qreal angle) {
    x = x * cos(angle) - y * sin(angle);
    y = x * sin(angle) + y * cos(angle);
}