#include "helper.h"

Helper::Helper() {}

void Helper::handleCollision(MovableCircle &circle, MovableRectangle &rect) const {
    if(contains(circle, rect)) {
        if(rect.getVx() != 0.) {
            qreal ballMass = circle.getMass();
            qreal boardMass = rect.getWidth() * rect.getHeight();
            qreal ballMomentum = ballMass*circle.getVx();
            qreal boardMomentum = boardMass*rect.getVx();
            qreal totalMomentum = ballMomentum + boardMomentum;
            qreal totalMass = ballMass + boardMass;
            circle.setVx(totalMomentum/totalMass);
        }
        circle.setVy(-circle.getVy());
        try {
            Brick& brick = dynamic_cast<Brick&>(rect);
            brick.setLife(brick.getLife() - 1);
        } catch(std::bad_cast) {
        }
    }
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