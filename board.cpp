#include "board.h"

Board::Board() {
}

Board::Board(QRectF rect, QColor color)
    :MovableRectangle(rect), ColorfulObject(color) {
}

Board::Board(qreal x, qreal y, qreal width, qreal height, QColor color)
    :MovableRectangle(x, y, width, height), ColorfulObject(color) {
}

Board::~Board() {
}