#ifndef MOVABLEOBJECT_H
#define MOVABLEOBJECT_H

#include "gameobject.h"
#include "vector2d.h"

class MovableObject : public GameObject {

public:
    MovableObject(qreal vx = 0, qreal vy = 0);
    MovableObject(Vector2D velocity);
    virtual ~MovableObject() = 0;

    const Vector2D& getVelocity() const;
    Vector2D& getVelocity();
    void setVelocity(Vector2D velocity);
    qreal getVx() const;
    void setVx(qreal vx);
    qreal getVy() const;
    void setVy(qreal vy);

    virtual void move() = 0;

private:
    Vector2D velocity;
};

#endif // MOVABLEOBJECT_H