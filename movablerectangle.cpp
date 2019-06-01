#include "movablerectangle.h"

MovableRectangle::MovableRectangle(qreal vx, qreal vy)
    :MovableObject(vx, vy) {
}

MovableRectangle::MovableRectangle(QRectF rect, qreal vx, qreal vy)
    :MovableRectangle(vx, vy) {
    this->rect = rect;
}

MovableRectangle::MovableRectangle(qreal x, qreal y, qreal width, qreal height, qreal vx, qreal vy)
    :MovableRectangle(QRectF(x, y, width, height), vx, vy) {
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
    this->rect.setRect(x, rect.y(), getWidth(), getHeight());
}

qreal MovableRectangle::getY() const {
    return this->rect.y();
}

void MovableRectangle::setY(qreal y) {
    this->rect.setRect(rect.x(), y, getWidth(), getHeight());
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

void MovableRectangle::move() {
    this->rect.setRect(getX() + getVx(), getY() + getVy(), getWidth(), getHeight());
}