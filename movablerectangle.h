#ifndef MOVABLERECTANGLE_H
#define MOVABLERECTANGLE_H

#include "movableobject.h"
#include <QRectF>

class MovableRectangle : public MovableObject {

public:
    MovableRectangle(qreal vx = 0, qreal vy = 0);
    MovableRectangle(QRectF point, qreal vx = 0, qreal vy = 0);
    MovableRectangle(qreal x, qreal y, qreal width, qreal height, qreal vx = 0, qreal vy = 0);
    virtual ~MovableRectangle() = 0;

    const QRectF& getRect() const;
    QRectF& getRect();
    void setRect(QRectF rect);
    qreal getX() const;
    void setX(qreal x);
    qreal getY() const;
    void setY(qreal y);
    qreal getWidth() const;
    void setWidth(qreal width);
    qreal getHeight() const;
    void setHeight(qreal height);

    void move();

private:
    QRectF rect;
};

#endif // MOVABLERECTANGLE_H