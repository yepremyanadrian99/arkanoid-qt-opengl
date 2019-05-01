#ifndef HELPER_H
#define HELPER_H

#include "ball.h"
#include "board.h"
#include <cmath>
#include <vector>

class Helper
{
public:
    Helper();

    bool contains(const Board&, const Ball&) const;
    bool contains(const Ball&, const Ball&) const;
    void handleCollision(Board&, Ball&) const;
    void handleCollision(Ball&, std::vector<Ball>&) const;
    qreal massOfCircle(const qreal) const;
};

#endif // HELPER_H