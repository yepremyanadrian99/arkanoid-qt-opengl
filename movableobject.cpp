#include "movableobject.h"

MovableObject::MovableObject(qreal vx, qreal vy)
    :velocity(vx, vy) {
}

MovableObject::MovableObject(Vector2D velocity)
    :velocity(velocity) {
}

MovableObject::~MovableObject() {
}

const Vector2D& MovableObject::getVelocity() const {
    return this->velocity;
}

Vector2D& MovableObject::getVelocity() {
    return this->velocity;
}

void MovableObject::setVelocity(Vector2D velocity) {
    this->velocity = velocity;
}

qreal MovableObject::getVx() const {
    return this->velocity.getX();
}

void MovableObject::setVx(qreal vx) {
    this->velocity.setX(vx);
}

qreal MovableObject::getVy() const {
    return this->velocity.getY();
}

void MovableObject::setVy(qreal vy) {
    this->velocity.setY(vy);
}