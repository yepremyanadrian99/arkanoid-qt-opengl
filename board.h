#ifndef BLOCK_H
#define BLOCK_H

#include "movablerectangle.h"
#include "colorfulobject.h"

class Board : public MovableRectangle, public ColorfulObject {

private:
    Board();

private:
    static Board *instance;

public:
    ~Board();
    static Board* getInstance();
};

#endif // BLOCK_H