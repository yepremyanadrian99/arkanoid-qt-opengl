#include "brick.h"

Brick::Brick() {
}

Brick::Brick(QRectF rect, QColor color, qreal life)
    :MovableRectangle(rect), ColorfulObject(color), DestroyableObject(life) {
}

Brick::Brick(qreal x, qreal y, qreal width, qreal height, QColor color, qreal life)
    :MovableRectangle(x, y, width, height), ColorfulObject(color), DestroyableObject(life) {
}

Brick::~Brick() {
}