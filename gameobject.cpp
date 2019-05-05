#include "gameobject.h"

GameObject::GameObject()
    :id(nextId++) {
}

GameObject::~GameObject() {
}

int GameObject::getId() const {
    return this->id;
}

int GameObject::nextId = 0;