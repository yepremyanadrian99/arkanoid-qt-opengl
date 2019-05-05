#ifndef HELPER_H
#define HELPER_H

#include <cmath>
#include <vector>
#include "movablecircle.h"
#include "movablerectangle.h"
#include "brick.h"

class Helper {

public:
    Helper();

    bool contains(const MovableCircle&, const MovableRectangle&) const;
    bool contains(const MovableCircle&, const MovableCircle&) const;
    void handleCollision(MovableCircle&, MovableRectangle&) const;
    void handleCollision(MovableCircle&, std::vector<MovableRectangle*>) const;
    void handleCollision(MovableCircle&, std::vector<MovableCircle*>) const;

};

#endif // HELPER_H