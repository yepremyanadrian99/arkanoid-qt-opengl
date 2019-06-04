#include "helper.h"
#include <iostream>

std::map<int, int> Helper::collapseMap;

bool Helper::handleCollision(MovableCircle &circle, MovableRectangle &rect) {
    if(rect.getId() == 0) {
        auto idToRemove = collapseMap.find(circle.getId());
        if(idToRemove != collapseMap.end()) {
            if(idToRemove->second == 0) {
                collapseMap.erase(idToRemove);
            } else {
                --idToRemove->second;
                return false;
            }
        }
    }

    auto collType = getCollisionType(circle, rect);
    bool collided = false;

    if(collType == COLLISION_TYPE::UP_DOWN_COLLISION) {
        collided = true;
        circle.getVelocity().reverseY();
    } else if(collType == COLLISION_TYPE::LEFT_RIGHT_COLLISION) {
        collided = true;
        circle.getVelocity().reverseX();
//        always move the ball up when hit by sides to not lose
        circle.setVy(-abs(circle.getVy()));
        if(rect.getId() == 0) {
            collapseMap[circle.getId()] = 100;
        }
    } else if(collType == COLLISION_TYPE::CORNER_COLLISION) {
        collided = true;
        circle.getVelocity().reverseX();
        circle.getVelocity().reverseY();
        circle.setX(circle.getX() + rect.getVx());
        if(rect.getId() == 0) {
            collapseMap[circle.getId()] = 100;
        }
    }

    if(collided && (abs(rect.getVx()) >= 0.1 || abs(rect.getVy()) >= 0.1)) {
        qreal vLen = circle.getVelocity().length();
        qreal alpha = std::atan2((circle.getVy() + rect.getVy()), (circle.getVx() + rect.getVx()));

        circle.setVx(vLen * cos(alpha));
        circle.setVy(vLen * sin(alpha));

        if(abs(circle.getVx()) < 0.5) {
            circle.setVx((circle.getVx() < 0 ? -0.5 : 0.5));
            circle.setVy(std::sqrt(4 - circle.getVx() * circle.getVx()) * (circle.getVy() < 0 ? -1 : 1));
        } else if(abs(circle.getVy()) < 0.5) {
            circle.setVy((circle.getVy() < 0 ? -0.5 : 0.5));
            circle.setVx(std::sqrt(4 - circle.getVy() * circle.getVy()) * (circle.getVx() < 0 ? -1 : 1));
        }

        circle.move();
    }

    return collided;
}

bool Helper::contains(const MovableCircle &circle, const MovableRectangle &rect) {
    qreal deltaX = circle.getPoint().x() - std::max(rect.getX(), std::min(circle.getPoint().x(), rect.getX() + rect.getWidth()));
    qreal deltaY = circle.getPoint().y() - std::max(rect.getY(), std::min(circle.getPoint().y(), rect.getY()+ rect.getHeight()));
    return (deltaX * deltaX + deltaY * deltaY) < (circle.getRadius() * circle.getRadius());
}

COLLISION_TYPE Helper::getCollisionType(const MovableCircle &circle, const MovableRectangle &rect) {
    qreal eps = circle.getVelocity().length();

    qreal cx = circle.getX();
    qreal cy = circle.getY();
    qreal cr = circle.getRadius();

    qreal rx = rect.getX();
    qreal ry = rect.getY();
    qreal rw = rect.getWidth();
    qreal rh = rect.getHeight();

    if(cx >= rx && cx <= (rx + rw) && (abs(abs(cy - ry) - cr) <= eps - 0.1 || abs(abs(cy - ry - rh) - cr) <= eps - 0.1)) {
        return COLLISION_TYPE::UP_DOWN_COLLISION;
    } else if(cy >= ry && cy <= ry + rh && (abs(abs(cx - rx) - cr) <= eps - 0.1 || abs(abs(cx - rx - rw) - cr) <= eps - 0.1)) {
        return COLLISION_TYPE::LEFT_RIGHT_COLLISION;
    } else if((cx - rx) * (cx - rx) + (cy - ry) * (cy - ry) <= cr * cr ||
           (cx - rx - rw) * (cx - rx - rw) + (cy - ry) * (cy - ry) <= cr * cr ||
           (cx - rx) * (cx - rx) + (cy - ry - rh) * (cy - ry - rh) <= cr * cr ||
           (cx - rx - rw) * (cx - rx - rw) + (cy - ry - rh) * (cy - ry - rh) <= cr * cr) {
        return COLLISION_TYPE::CORNER_COLLISION;
    }
    return COLLISION_TYPE::NONE;
}

void Helper::handleBallOutsideMap(MovableCircle &circle, int width, int height) {
    if(circle.getX() + circle.getRadius() / 2 > width) {
        circle.setX(width - circle.getRadius() / 2);
    }
    if(circle.getX() - circle.getRadius() / 2 < 0) {
        circle.setX(circle.getRadius() / 2);
    }
    if(circle.getY() + circle.getRadius() / 2 > height) {
        circle.setY(height - circle.getRadius() / 2);
    }
    if(circle.getY() - circle.getRadius() / 2 < 0) {
        circle.setY(circle.getRadius() / 2);
    }
}