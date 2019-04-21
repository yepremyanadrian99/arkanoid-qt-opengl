#include "helper.h"

Helper::Helper()
{
}

void Helper::handleCollision(Board& board, Ball& ball) {
    if(contains(board, ball)) {
        if(board.getVx() != 0.) {
            qreal ballMass = M_PI*ball.getRadius()*ball.getRadius();
            qreal boardMass = board.getWidth()*board.getHeight();
            qreal ballMomentum = ballMass*ball.getVx();
            qreal boardMomentum = boardMass*board.getVx();
            qreal totalMomentum = ballMomentum + boardMomentum;
            qreal totalMass = ballMass + boardMass;
            ball.setVx(totalMomentum/totalMass);
        }
        ball.setVy(-ball.getVy());
    }
}

bool Helper::contains(const Board &board, const Ball &ball) {
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
