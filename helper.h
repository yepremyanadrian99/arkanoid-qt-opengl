#ifndef HELPER_H
#define HELPER_H

#include <QTimer>
#include <cmath>
#include <vector>
#include <map>
#include "movablecircle.h"
#include "movablerectangle.h"
#include "brick.h"

class Helper {
private:
    mutable std::map<int, int> collapseMap;

    enum COLLISION_TYPE {
        UP_DOWN_COLLISION,
        LEFT_RIGHT_COLLISION,
        CORNER_COLLISION,
        NONE
    };

public:
    bool contains(const MovableCircle &circle, const MovableRectangle &rect) const;
    void handleCollision(MovableCircle &circle, MovableRectangle &rect) const;
    void handleCollision(MovableCircle &circle, std::vector<MovableRectangle*> rects) const;
    void handleBallOutsideMap(MovableCircle &circle, int width, int height) const;
    COLLISION_TYPE getCollisionType(const MovableCircle &circle, const MovableRectangle &rect) const;
};

#endif // HELPER_H