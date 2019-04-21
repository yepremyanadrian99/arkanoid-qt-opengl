#include "ball.h"

qreal Ball::getVx() const {
    return this->vx;
}

void Ball::setVx(qreal vx) {
    this->vx = vx;
}

qreal Ball::getVy() const {
    return this->vy;
}

void Ball::setVy(qreal vy) {
    this->vy = vy;
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
    this->point.setX(this->point.x() + vx);
    this->point.setY(this->point.y() + vy);
}

bool Ball::contains(const Ball& ball) {
    qreal x1 = this->point.x();
    qreal y1 = this->point.y();
    qreal x2 = ball.point.x();
    qreal y2 = ball.point.y();
    qreal distance = std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return distance < ball.radius + this->radius;
}
