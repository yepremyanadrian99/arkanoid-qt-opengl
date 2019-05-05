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