#include <destroyableobject.h>

DestroyableObject::DestroyableObject() {
}

DestroyableObject::DestroyableObject(qreal life)
    :life(life) {
}

DestroyableObject::~DestroyableObject() {
}

qreal DestroyableObject::getLife() const {
    return this->life;
}

void DestroyableObject::setLife(qreal life) {
    this->life = life;
}

void DestroyableObject::hit() {
    --this->life;
}

bool DestroyableObject::isDestroyed() const {
    return this->life <= 0;
}