#ifndef BLOCK_H
#define BLOCK_H

#include "movableobject.h"
#include <QPointF>
#include <QRectF>

class Board : public MovableObject
{
public:
    Board() {}
    Board(QRectF rect)
        :rect(rect) {}
    Board(qreal x, qreal y, qreal width, qreal height);

    const QRectF getRect() const;
    void setRect(QRectF);
    qreal getX() const;
    void setX(qreal);
    qreal getY() const;
    void setY(qreal);
    qreal getWidth() const;
    void setWidth(qreal);
    qreal getHeight() const;
    void setHeight(qreal);

    void move();

private:
    QRectF rect;
};

#endif // BLOCK_H
