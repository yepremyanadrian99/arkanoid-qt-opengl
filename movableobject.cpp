#include "movableobject.h"

MovableObject::MovableObject()
    :vx(0), vy(0) {
}

MovableObject::~MovableObject() {
}

qreal MovableObject::getVx() const {
    return this->vx;
}

void MovableObject::setVx(qreal vx) {
    this->vx = vx;
}

qreal MovableObject::getVy() const {
    return this->vy;
}

void MovableObject::setVy(qreal vy) {
    this->vy = vy;
}
