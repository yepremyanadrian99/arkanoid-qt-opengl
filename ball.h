#ifndef BALL_H
#define BALL_H

#include "movablecircle.h"
#include "colorfulobject.h"

class Ball : public MovableCircle, public ColorfulObject {

public:
    Ball();
    Ball(QPointF, qreal, QColor = Qt::red);
    Ball(qreal, qreal, qreal, QColor = Qt::red);
    ~Ball();

};

#endif // BALL_H