#ifndef HELPER_H
#define HELPER_H

#include "ball.h"
#include "board.h"
#include <cmath>

class Helper
{
public:
    Helper();

    bool contains(const Board&, const Ball&);
    void handleCollision(Board&, Ball&);
};

#endif // HELPER_H
