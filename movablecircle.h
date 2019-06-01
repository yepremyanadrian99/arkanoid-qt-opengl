#ifndef MOVABLECIRCLE_H
#define MOVABLECIRCLE_H

#include <cmath>
#include "movableobject.h"
#include <QPointF>

class MovableCircle : public MovableObject {

public:
    MovableCircle(qreal vx = 0, qreal vy = 0);
    MovableCircle(QPointF point, qreal radius, qreal vx = 0, qreal vy = 0);
    MovableCircle(qreal x, qreal y, qreal radius, qreal vx = 0, qreal vy = 0);
    virtual ~MovableCircle() = 0;

    qreal getRadius() const;
    void setRadius(qreal radius);
    QPointF& getPoint();
    const QPointF& getPoint() const;
    void setPoint(QPointF point);
    qreal getX() const;
    void setX(qreal x);
    qreal getY() const;
    void setY(qreal y);

    void move();

private:
    QPointF point;
    qreal radius;
};

#endif // MOVABLECIRCLE_H