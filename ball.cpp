#include "ball.h"

Ball::Ball() {
}

Ball::Ball(QPointF point, qreal radius, QColor color)
    :MovableCircle(point, radius), ColorfulObject(color) {
}

Ball::Ball(qreal x, qreal y, qreal radius, QColor color)
    :MovableCircle(x, y, radius), ColorfulObject(color) {
}

Ball::~Ball() {
}