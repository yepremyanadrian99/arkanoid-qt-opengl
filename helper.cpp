#include "helper.h"

Helper::Helper() {}

void Helper::handleCollision(MovableCircle &circle, MovableRectangle &rect) const {
    qreal deltaX = circle.getPoint().x() - std::max(rect.getX(), std::min(circle.getPoint().x(), rect.getX() + rect.getWidth()));
    qreal deltaY = circle.getPoint().y() - std::max(rect.getY(), std::min(circle.getPoint().y(), rect.getY()+ rect.getHeight()));

    qreal eps = std::sqrt(circle.getVx() * circle.getVx() + circle.getVy() * circle.getVy());

    qreal cx = circle.getPoint().x();
    qreal cy = circle.getPoint().y();
    qreal cr = circle.getRadius();

    qreal rx = rect.getX();
    qreal ry = rect.getY();
    qreal rw = rect.getWidth();
    qreal rh = rect.getHeight();

    bool collided = false;
    if(cx >= rx && cx <= rx + rw && (abs(abs(cy - ry) - cr) <= eps || abs(abs(cy - ry - rh) - cr) <= eps)) {
        circle.setVy(-circle.getVy());
        collided = true;
    }
    else if(cy >= ry && cy <= ry + rh && (abs(abs(cx - rx) - cr) <= eps || abs(abs(cx - rx - rw) - cr) <= eps)) {
        circle.setVx(-circle.getVx());
        collided = true;
    }
    else if((cx - rx) * (cx - rx) + (cy - ry) * (cy - ry) <= cr * cr ||
            (cx - rx - rw) * (cx - rx - rw) + (cy - ry) * (cy - ry) <= cr * cr ||
            (cx - rx) * (cx - rx) + (cy - ry - rh) * (cy - ry - rh) <= cr * cr ||
            (cx - rx - rw) * (cx - rx - rw) + (cy - ry - rh) * (cy - ry - rh) <= cr * cr) {
        circle.setVx(-circle.getVx());
        circle.setVy(-circle.getVy());
        collided = true;
    }

    if(collided && (abs(rect.getVx()) >= 0.1 || abs(rect.getVy()) >= 0.1)) {
        qreal v = std::sqrt(circle.getVx() * circle.getVx() + circle.getVy() * circle.getVy());
        qreal alpha = std::atan2((circle.getVy() + rect.getVy()), (circle.getVx() + rect.getVx()));

        circle.setVx(v * cos(alpha));
        circle.setVy(v * sin(alpha));

        if(abs(circle.getVx()) < 0.1)
        {
            circle.setVx((circle.getVx() < 0 ? -1 : 1));
            circle.setVy(std::sqrt(16 - circle.getVx() * circle.getVx()) * (circle.getVy() < 0 ? -1 : 1));
        }
        else if(abs(circle.getVy()) < 0.1)
        {
            circle.setVy((circle.getVy() < 0 ? -1 : 1));
            circle.setVx(std::sqrt(16 - circle.getVy() * circle.getVy()) * (circle.getVx() < 0 ? -1 : 1));
        }
    }


//    if(contains(circle, rect, 0))
//    {
//        circle.setVx(-circle.getVx());
//        circle.setVy(-circle.getVy());
//        while(contains(circle, rect, 0)) {
//            circle.move();
//        }
//        return;
//    }

//    if(contains(circle, rect)) {
//        if(rect.getVx() != 0.) {
//            qreal ballMass = circle.getMass();
//            qreal boardMass = rect.getWidth() * rect.getHeight();
//            qreal ballMomentum = ballMass*circle.getVx();
//            qreal boardMomentum = boardMass*rect.getVx();
//            qreal totalMomentum = ballMomentum + boardMomentum;
//            qreal totalMass = ballMass + boardMass;
//            circle.setVx(totalMomentum/totalMass);

//        }
//        circle.setVy(-circle.getVy());
//        try {
//            Brick& brick = dynamic_cast<Brick&>(rect);
//           brick.setLife(brick.getLife() - 1);
//        } catch(std::bad_cast) {
//        }
//    }
}

void Helper::handleCollision(MovableCircle &circle, std::vector<MovableRectangle*> rects) const {
    for(size_t i = 0; i < rects.size(); ++i) {
        handleCollision(circle, *rects[i]);
    }
}

void Helper::handleCollision(MovableCircle &circle, std::vector<MovableCircle*> circles) const {
    for(size_t i = 0; i < circles.size(); ++i) {
        if(circle.getId() != circles[i]->getId() &&
                contains(circle, *circles[i])) {
            qreal m1 = circle.getMass();
            qreal m2 = circles[i]->getMass();
            qreal totalM = m1 + m2;
            qreal vx1 = circle.getVx();
            qreal vy1 = circle.getVy();
            qreal vx2 = circles[i]->getVx();
            qreal vy2 = circles[i]->getVy();

            circle.setVx(((m1 - m2)/totalM)*vx1 + (2*m2/totalM)*vx2);
            circle.setVy(((m1 - m2)/totalM)*vy1 + (2*m2/totalM)*vy2);
            circles[i]->setVx(((m2 - m1)/totalM)*vx2 + (2*m1/totalM)*vx1);
            circles[i]->setVy(((m2 - m1)/totalM)*vy2 + (2*m1/totalM)*vy1);
        }
    }
}

bool Helper::contains(const MovableCircle &circle, const MovableRectangle &rect) const {
    qreal deltaX = circle.getPoint().x() - std::max(rect.getX(), std::min(circle.getPoint().x(), rect.getX() + rect.getWidth()));
    qreal deltaY = circle.getPoint().y() - std::max(rect.getY(), std::min(circle.getPoint().y(), rect.getY()+ rect.getHeight()));
    return (deltaX * deltaX + deltaY * deltaY) < (circle.getRadius() * circle.getRadius());
}

bool Helper::contains(const MovableCircle &ball1, const MovableCircle &ball2) const {
    qreal x1 = ball1.getPoint().x();
    qreal y1 = ball1.getPoint().y();
    qreal x2 = ball2.getPoint().x();
    qreal y2 = ball2.getPoint().y();
    qreal distance = std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return distance <= ball1.getRadius() + ball2.getRadius();
}

bool Helper::contains(const MovableCircle& ball, const MovableRectangle& rect, int) const {
    qreal x = ball.getPoint().x();
    qreal y = ball.getPoint().y();
    qreal r = ball.getRadius();

    std::vector<std::pair<qreal, qreal>> rect_borders = { {rect.getX(), rect.getY()},
                                                          {rect.getX() + rect.getWidth(), rect.getY()},
                                                          {rect.getX(), rect.getY() + rect.getHeight()},
                                                          {rect.getX() + rect.getWidth(), rect.getY() + rect.getHeight()} };

    for(size_t i = 0; i < rect_borders.size(); ++i) {
        qreal rx = rect_borders[i].first;
        qreal ry = rect_borders[i].second;

        if((x - rx) * (x - rx) + (y - ry) * (y - ry) < r * r)
        {
            return true;
        }
    }

    return false;
}

void Helper::changeDirection(MovableCircle& ball, const MovableRectangle& rect) const
{

}


















