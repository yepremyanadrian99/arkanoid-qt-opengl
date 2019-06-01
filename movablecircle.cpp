#include "movablecircle.h"

MovableCircle::MovableCircle(qreal vx, qreal vy)
    :MovableObject (vx, vy) {
}

MovableCircle::MovableCircle(QPointF point, qreal radius, qreal vx, qreal vy)
    :MovableCircle(vx, vy) {
    this->point = point;
    this->radius = radius;
}

MovableCircle::MovableCircle(qreal x, qreal y, qreal radius, qreal vx, qreal vy)
    :MovableCircle(QPointF(x, y), radius, vx, vy) {
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

qreal MovableCircle::getX() const {
    return this->getPoint().x();
}

void MovableCircle::setX(qreal x) {
    this->point = QPointF(x, point.y());
}

qreal MovableCircle::getY() const {
    return this->getPoint().y();
}

void MovableCircle::setY(qreal y) {
    this->point = QPointF(point.x(), y);
}

void MovableCircle::move() {
    this->getPoint().setX(this->getPoint().x() + getVx());
    this->getPoint().setY(this->getPoint().y() + getVy());
}