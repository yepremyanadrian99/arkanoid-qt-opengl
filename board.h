#ifndef BLOCK_H
#define BLOCK_H

#include <QPointF>
#include <QRectF>

class Board
{
public:
    Board() {}
    Board(QRectF rect)
        :rect(rect){}
    Board(qreal x, qreal y, qreal width, qreal height);

    const QRectF getRect() const;
    void setRect(QRectF);
    qreal getX() const;
    void setX(qreal);
    qreal getY() const;
    void setY(qreal);
    qreal getVx() const;
    void setVx(qreal);
    qreal getVy() const;
    void setVy(qreal);
    qreal getWidth() const;
    void setWidth(qreal);
    qreal getHeight() const;
    void setHeight(qreal);

    void move();

private:
    QRectF rect;
    qreal vx;
    qreal vy;
};

#endif // BLOCK_H
