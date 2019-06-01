#include "board.h"

Board::Board() {
}

Board::Board(QRectF rect, qreal vx, qreal vy, QColor color)
    :MovableRectangle(rect, vx, vy), ColorfulObject(color) {
}

Board::Board(qreal x, qreal y, qreal width, qreal height, qreal vx, qreal vy, QColor color)
    :MovableRectangle(x, y, width, height, vx, vy), ColorfulObject(color) {
}

Board::~Board() {
}