#ifndef BLOCK_H
#define BLOCK_H

#include "movablerectangle.h"
#include "colorfulobject.h"

class Board : public MovableRectangle, public ColorfulObject {

public:
    Board();
    Board(QRectF point, qreal vx = 0, qreal vy = 0, QColor color = Qt::darkGray);
    Board(qreal x, qreal y, qreal width, qreal height, qreal vx = 0, qreal vy = 0, QColor color = Qt::darkGray);
    ~Board();
};

#endif // BLOCK_H