#ifndef BALL_H
#define BALL_H

#include "movablecircle.h"
#include "destroyableobject.h"
#include "colorfulobject.h"

class Ball : public MovableCircle, public DestroyableObject, public ColorfulObject {

public:
    Ball();
    Ball(QPointF point, qreal radius, qreal vx = 0, qreal vy = 0, QColor color = Qt::red);
    Ball(qreal x, qreal y, qreal radius, qreal vx = 0, qreal vy = 0, QColor color = Qt::red);
    ~Ball();
};

#endif // BALL_H