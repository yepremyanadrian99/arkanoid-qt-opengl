#ifndef BALL_H
#define BALL_H

#include <QPointF>
#include <cmath>

class Ball
{
public:
    Ball() {}

    Ball(qreal x, qreal y)
        :point(x, y) {}

    Ball(QPointF point)
        :point(point) {}

    Ball(qreal x, qreal y, qreal radius)
        :point(x, y), radius(radius) {}

    Ball (QPointF point, qreal radius)
        :point(point), radius(radius) {}

    qreal getVx() const;
    void setVx(qreal);
    qreal getVy() const;
    void setVy(qreal);
    qreal getRadius() const;
    void setRadius(qreal);
    const QPointF getPoint() const;
    void setPoint(QPointF point);

    void move();
    bool contains(const Ball&);

private:
    QPointF point;
    qreal vx, vy;
    qreal radius;
};

#endif // BALL_H
