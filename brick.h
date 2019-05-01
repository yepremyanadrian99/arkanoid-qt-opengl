#ifndef BRICK_H
#define BRICK_H

#include "movableobject.h"
#include <QRectF>
#include <QColor>

class Brick : public MovableObject
{    
public:
    Brick();

    QRectF getRect() const;
    void setRect(QRectF) const;

private:
    QRectF rect;
    QColor color;
    qreal life;
};

#endif // BRICK_H
