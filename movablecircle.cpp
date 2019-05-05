#include "movablecircle.h"

MovableCircle::MovableCircle() {
}

MovableCircle::MovableCircle(QPointF point, qreal radius)
    :point(point), radius(radius) {
}

MovableCircle::MovableCircle(qreal x, qreal y, qreal radius)
    :MovableCircle(QPointF(x, y), radius) {
}

MovableCircle::~MovableCircle() {
}

qreal MovableCircle::getRadius() const {
    return this->radius;
}

void MovableCircle::setRadius(qreal radius) {
    this->radius = radius;
}

QPointF& MovableCircle::getPoint() {
    return this->point;
}

const QPointF& MovableCircle::getPoint() const {
    return this->point;
}

void MovableCircle::setPoint(QPointF point) {
    this->point = point;
}

qreal MovableCircle::getMass() const {
    return M_PI * radius * radius;
}

void MovableCircle::move() {
    qreal delta_t = 1.35;
    this->getPoint().setX(this->getPoint().x() + getVx() * delta_t);
    this->getPoint().setY(this->getPoint().y() + getVy() * delta_t);
}