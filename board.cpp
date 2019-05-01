#include "board.h"

Board::Board(qreal x, qreal y, qreal width, qreal height) {
    rect = QRectF(x, y, width, height);
}

const QRectF Board::getRect() const {
    return this->rect;
}

void Board::setRect(QRectF rect) {
    this->rect = rect;
}

qreal Board::getX() const {
    return this->rect.x();
}

void Board::setX(qreal x) {
    this->rect.setRect(x, getY(), getWidth(), getHeight());
}

qreal Board::getY() const {
    return this->rect.y();
}

void Board::setY(qreal y) {
    this->rect.setRect(getX(), y, getWidth(), getHeight());
}

qreal Board::getWidth() const {
    return this->rect.width();
}

void Board::setWidth(qreal width) {
    this->rect.setWidth(width);
}

qreal Board::getHeight() const {
    return this->rect.height();
}

void Board::setHeight(qreal height) {
    this->rect.setHeight(height);
}

void Board::move() {
    this->rect.setRect(getX() + getVx(), getY() + getVy(), getWidth(), getHeight());
}
