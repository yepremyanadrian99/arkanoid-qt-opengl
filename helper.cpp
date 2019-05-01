#include "helper.h"

Helper::Helper() {}

void Helper::handleCollision(Board &board, Ball &ball) const {
    if(contains(board, ball)) {
        if(board.getVx() != 0.) {
            qreal ballMass = massOfCircle(ball.getRadius());
            qreal boardMass = board.getWidth() * board.getHeight();
            qreal ballMomentum = ballMass*ball.getVx();
            qreal boardMomentum = boardMass*board.getVx();
            qreal totalMomentum = ballMomentum + boardMomentum;
            qreal totalMass = ballMass + boardMass;
            ball.setVx(totalMomentum/totalMass);
        }
        ball.setVy(-ball.getVy());
    }
}

void Helper::handleCollision(Ball &ball, std::vector<Ball> &balls) const {
    for(size_t i = 0; i < balls.size(); ++i) {
        if(ball.getId() != balls[i].getId() &&
                contains(ball, balls[i])) {

            qreal m1 = massOfCircle(ball.getRadius());
            qreal m2 = massOfCircle(balls[i].getRadius());
            qreal totalM = m1 + m2;
            qreal vx1 = ball.getVx();
            qreal vy1 = ball.getVy();
            qreal vx2 = balls[i].getVx();
            qreal vy2 = balls[i].getVy();

            ball.setVx(((m1 - m2)/totalM)*vx1 + (2*m2/totalM)*vx2);
            ball.setVy(((m1 - m2)/totalM)*vy1 + (2*m2/totalM)*vy2);
            balls[i].setVx(((m2 - m1)/totalM)*vx2 + (2*m1/totalM)*vx1);
            balls[i].setVy(((m2 - m1)/totalM)*vy2 + (2*m1/totalM)*vy1);
        }
    }
}

bool Helper::contains(const Board &board, const Ball &ball) const {
    qreal circleDistanceX = abs(ball.getPoint().x() - board.getRect().x() - board.getRect().width()/2);
    qreal circleDistanceY = abs(ball.getPoint().y() - board.getRect().y() - board.getRect().height()/2);

    if (circleDistanceX > (board.getRect().width()/2 + ball.getRadius())) { return false; }
    if (circleDistanceY > (board.getRect().height()/2 + ball.getRadius())) { return false; }

    if (circleDistanceX < (board.getRect().width()/2)) { return true; }
    if (circleDistanceY < (board.getRect().height()/2)) { return true; }

    qreal cornerDistance_sq = (circleDistanceX - board.getRect().width()/2)*(circleDistanceX - board.getRect().width()/2) +
            (circleDistanceY - board.getRect().height()/2)*(circleDistanceY - board.getRect().height()/2);

    return (cornerDistance_sq < (ball.getRadius()*ball.getRadius()));
}

bool Helper::contains(const Ball &ball1, const Ball &ball2) const {
    qreal x1 = ball1.getPoint().x();
    qreal y1 = ball1.getPoint().y();
    qreal x2 = ball2.getPoint().x();
    qreal y2 = ball2.getPoint().y();
    qreal distance = std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return distance <= ball1.getRadius() + ball2.getRadius();
}

qreal Helper::massOfCircle(const qreal radius) const {
    return M_PI * radius * radius;
}