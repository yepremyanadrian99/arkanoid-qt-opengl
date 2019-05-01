#ifndef BALL_H
#define BALL_H

#include "movableobject.h"
#include <QPointF>
#include <cmath>

class Ball : public MovableObject
{
public:
    Ball()
        :id(nextId++) {}

    Ball(qreal x, qreal y)
        :id(nextId++), point(x, y) {}

    Ball(QPointF point)
        :id(nextId++), point(point) {}

    Ball(qreal x, qreal y, qreal radius)
        :id(nextId++), point(x, y), radius(radius) {}

    Ball(QPointF point, qreal radius)
        :id(nextId++), point(point), radius(radius) {}

    int getId() const;
    qreal getRadius() const;
    void setRadius(qreal);
    const QPointF getPoint() const;
    void setPoint(QPointF point);

    void move();
    bool contains(const Ball&);

private:
    static int nextId;
    const int id;
    QPointF point;
    qreal radius;
};

#endif // BALL_H
