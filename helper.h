#ifndef HELPER_H
#define HELPER_H

#include <QTimer>
#include <cmath>
#include <vector>
#include <map>
#include "movablecircle.h"
#include "movablerectangle.h"
#include "brick.h"

enum COLLISION_TYPE {
    UP_DOWN_COLLISION,
    LEFT_RIGHT_COLLISION,
    CORNER_COLLISION,
    NONE
};

namespace Helper {
    extern std::map<int, int> collapseMap;

    bool contains(const MovableCircle &circle, const MovableRectangle &rect);
    bool handleCollision(MovableCircle &circle, MovableRectangle &rect);
    void handleCollision(MovableCircle &circle, std::vector<MovableRectangle*> rects);
    void handleBallOutsideMap(MovableCircle &circle, int width, int height);
    COLLISION_TYPE getCollisionType(const MovableCircle &circle, const MovableRectangle &rect);
}

#endif // HELPER_H