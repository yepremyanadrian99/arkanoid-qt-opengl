#ifndef BLOCK_H
#define BLOCK_H

#include "movablerectangle.h"
#include "colorfulobject.h"

class Board : public MovableRectangle, public ColorfulObject {

public:
    Board();
    Board(QRectF, QColor = Qt::darkGray);
    Board(qreal, qreal, qreal, qreal, QColor = Qt::darkGray);
    ~Board();

};

#endif // BLOCK_H