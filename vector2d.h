#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cmath>
#include <QtGlobal>

class Vector2D {

public:
    Vector2D();
    Vector2D(qreal x, qreal y);

    qreal getX() const;
    void setX(qreal x);
    qreal getY() const;
    void setY(qreal y);
    void reverseX();
    void reverseY();
    qreal length() const;
    void rotate(qreal angle);

private:
    qreal x;
    qreal y;
};

#endif // VECTOR2D_H
