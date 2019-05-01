#ifndef MOVABLEOBJECT_H
#define MOVABLEOBJECT_H

#include <QPointF>

class MovableObject
{
public:
    MovableObject();

    qreal getVx() const;
    void setVx(qreal);
    qreal getVy() const;
    void setVy(qreal);

private:
    qreal vx;
    qreal vy;
};

#endif // MOVABLEOBJECT_H
