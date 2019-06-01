#include "gameobject.h"

GameObject::GameObject()
    :id(getNextId()) {
}

GameObject::~GameObject() {
}

int GameObject::getNextId() {
    return nextId++;
}

int GameObject::getId() const {
    return this->id;
}

int GameObject::nextId = 0;