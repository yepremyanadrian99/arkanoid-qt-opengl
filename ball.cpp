#include "ball.h"

int Ball::getId() const {
    return this->id;
}

qreal Ball::getRadius() const {
    return this->radius;
}

void Ball::setRadius(qreal radius) {
    this->radius = radius;
}

const QPointF Ball::getPoint() const {
    return this->point;
}

void Ball::setPoint(QPointF point) {
    this->point = point;
}

void Ball::move() {
    qreal delta_t = 1.35;
    this->point.setX(this->point.x() + getVx() * delta_t);
    this->point.setY(this->point.y() + getVy() * delta_t);
}

bool Ball::contains(const Ball& ball) {
    qreal x1 = this->point.x();
    qreal y1 = this->point.y();
    qreal x2 = ball.point.x();
    qreal y2 = ball.point.y();
    qreal distance = std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return distance < ball.radius + this->radius;
}

int Ball::nextId = 0;