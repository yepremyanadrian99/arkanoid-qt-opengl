#ifndef MOVABLEOBJECT_H
#define MOVABLEOBJECT_H

#include "gameobject.h"

class MovableObject : public GameObject {

public:
    MovableObject();
    virtual ~MovableObject();

    qreal getVx() const;
    void setVx(qreal);
    qreal getVy() const;
    void setVy(qreal);

    virtual qreal getMass() const = 0;
    virtual void move() = 0;

private:
    qreal vx;
    qreal vy;

};

#endif // MOVABLEOBJECT_H
