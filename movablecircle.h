#ifndef MOVABLECIRCLE_H
#define MOVABLECIRCLE_H

#include <cmath>
#include "movableobject.h"
#include <QPointF>

class MovableCircle : public MovableObject {

public:
    MovableCircle();
    MovableCircle(QPointF, qreal);
    MovableCircle(qreal, qreal, qreal);
    virtual ~MovableCircle();

    qreal getRadius() const;
    void setRadius(qreal);
    QPointF& getPoint();
    const QPointF& getPoint() const;
    void setPoint(QPointF point);

    qreal getMass() const;
    void move();

private:
    QPointF point;
    qreal radius;

};

#endif // MOVABLECIRCLE_H