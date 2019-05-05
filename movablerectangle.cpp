#include "movablerectangle.h"

MovableRectangle::MovableRectangle() {
}

MovableRectangle::MovableRectangle(QRectF rect)
    :rect(rect) {
}

MovableRectangle::MovableRectangle(qreal x, qreal y, qreal width, qreal height)
    :MovableRectangle(QRectF(x, y, width, height)) {
}

MovableRectangle::~MovableRectangle() {
}

const QRectF& MovableRectangle::getRect() const {
    return this->rect;
}

QRectF& MovableRectangle::getRect() {
    return this->rect;
}

void MovableRectangle::setRect(QRectF rect) {
    this->rect = rect;
}

qreal MovableRectangle::getX() const {
    return this->rect.x();
}

void MovableRectangle::setX(qreal x) {
    this->rect.setX(x);
}

qreal MovableRectangle::getY() const {
    return this->rect.y();
}

void MovableRectangle::setY(qreal y) {
    this->rect.setY(y);
}

qreal MovableRectangle::getWidth() const {
    return this->rect.width();
}

void MovableRectangle::setWidth(qreal width) {
    this->rect.setWidth(width);
}

qreal MovableRectangle::getHeight() const {
    return this->rect.height();
}

void MovableRectangle::setHeight(qreal height) {
    this->rect.setHeight(height);
}

qreal MovableRectangle::getMass() const {
    return getRect().width() * getRect().height();
}

void MovableRectangle::move() {
    this->rect.setRect(getX() + getVx(), getY() + getVy(), getWidth(), getHeight());
}