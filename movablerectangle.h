#ifndef MOVABLERECTANGLE_H
#define MOVABLERECTANGLE_H

#include "movableobject.h"
#include <QRectF>

class MovableRectangle : public MovableObject {

public:
    MovableRectangle();
    MovableRectangle(QRectF);
    MovableRectangle(qreal x, qreal y, qreal width, qreal height);
    virtual ~MovableRectangle();

    const QRectF& getRect() const;
    QRectF& getRect();
    void setRect(QRectF);
    qreal getX() const;
    void setX(qreal);
    qreal getY() const;
    void setY(qreal);
    qreal getWidth() const;
    void setWidth(qreal);
    qreal getHeight() const;
    void setHeight(qreal);

    qreal getMass() const;
    void move();

private:
    QRectF rect;

};

#endif // MOVABLERECTANGLE_H
