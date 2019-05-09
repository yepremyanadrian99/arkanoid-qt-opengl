#ifndef BRICK_H
#define BRICK_H

#include "movablerectangle.h"
#include "colorfulobject.h"
#include "destroyableobject.h"

class Brick : public MovableRectangle,  public ColorfulObject, public DestroyableObject {

public:
    Brick();
    Brick(QRectF, QColor = Qt::blue, qreal = 1);
    Brick(qreal x, qreal y, qreal width, qreal height, QColor = Qt::blue, qreal = 1);
    ~Brick();

};

#endif // BRICK_H
