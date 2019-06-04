#ifndef BLOCK_H
#define BLOCK_H

#include "movablerectangle.h"
#include "colorfulobject.h"

class Board : public MovableRectangle, public ColorfulObject {

private:
    Board();

public:
     Board(const Board&) = delete;
     Board& operator=(const Board&) = delete;

    static Board& getInstance();
};

#endif // BLOCK_H