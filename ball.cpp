#include "ball.h"

Ball::Ball() {
}

Ball::Ball(QPointF point, qreal radius, qreal vx, qreal vy, QColor color)
    :MovableCircle(point, radius, vx, vy), ColorfulObject(color) {
}

Ball::Ball(qreal x, qreal y, qreal radius, qreal vx, qreal vy, QColor color)
    :MovableCircle(x, y, radius, vx, vy), ColorfulObject(color) {
}

Ball::~Ball() {
}