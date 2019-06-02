#ifndef HELPER_H
#define HELPER_H

#include <QTimer>
#include <cmath>
#include <vector>
#include <map>
#include "movablecircle.h"
#include "movablerectangle.h"
#include "brick.h"

extern std::map<int, int> collapseMap;

enum COLLISION_TYPE {
    UP_DOWN_COLLISION,
    LEFT_RIGHT_COLLISION,
    CORNER_COLLISION,
    NONE
};

class Helper {

public:
    static bool contains(const MovableCircle &circle, const MovableRectangle &rect);
    static bool handleCollision(MovableCircle &circle, MovableRectangle &rect);
    static void handleCollision(MovableCircle &circle, std::vector<MovableRectangle*> rects);
    static void handleBallOutsideMap(MovableCircle &circle, int width, int height);
    static COLLISION_TYPE getCollisionType(const MovableCircle &circle, const MovableRectangle &rect);
};

#endif // HELPER_H