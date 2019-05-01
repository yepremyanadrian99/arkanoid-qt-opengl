#include "mainwindow.h"

MainWindow::MainWindow(QGLWidget *parent)
    : QGLWidget(parent) {

    this->setGeometry(100, 100, 800, 600);
    this->updateGL();

    helper = Helper();

    board = Board(20, this->height() - 25, 100, 25);
    board.setVx(0);
    board.setVy(0);

    balls = std::vector<Ball>();

    Ball ball1(100, 150, 20);
    ball1.setVx(0.5);
    ball1.setVy(-0.5);

    Ball ball2(400, 150, 20);
    ball2.setVx(-0.25);
    ball2.setVy(-0.75);

    Ball ball3(300, 150, 20);
    ball3.setVx(0.20);
    ball3.setVy(-0.80);

    Ball ball4(200, 150, 20);
    ball4.setVx(0.5);
    ball4.setVy(-0.5);

    Ball ball5(400, 250, 20);
    ball5.setVx(-0.25);
    ball5.setVy(-0.75);

    Ball ball6(300, 350, 20);
    ball6.setVx(0.20);
    ball6.setVy(-0.80);

    Ball ball7(100, 300, 20);
    ball7.setVx(0.5);
    ball7.setVy(-0.5);

    Ball ball8(400, 100, 20);
    ball8.setVx(-0.25);
    ball8.setVy(-0.75);

    Ball ball9(300, 40, 20);
    ball9.setVx(0.20);
    ball9.setVy(-0.80);

    balls.push_back(ball1);
    balls.push_back(ball2);
    balls.push_back(ball3);
    balls.push_back(ball4);
    balls.push_back(ball5);
    balls.push_back(ball6);
    balls.push_back(ball7);
    balls.push_back(ball8);
    balls.push_back(ball9);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->start(5);
}

MainWindow::~MainWindow() {}

void MainWindow::animate() {
    update();
}

bool checkBallColls(Ball &ball, std::vector<Ball> &balls, Helper &helper) {
    for(size_t i = 0; i < balls.size(); ++i) {
        if(ball.getId() != balls[i].getId() &&
                helper.contains(ball, balls[i])) {

            qreal m1 = helper.massOfCircle(ball.getRadius());
            qreal m2 = helper.massOfCircle(balls[i].getRadius());
            qreal totalM = m1 + m2;
            qreal vx1 = ball.getVx();
            qreal vy1 = ball.getVy();
            qreal vx2 = balls[i].getVx();
            qreal vy2 = balls[i].getVy();

            ball.setVx(((m1 - m2)/totalM)*vx1 + (2*m2/totalM)*vx2);
            ball.setVy(((m1 - m2)/totalM)*vy1 + (2*m2/totalM)*vy2);
            balls[i].setVx(((m2 - m1)/totalM)*vx2 + (2*m1/totalM)*vx1);
            balls[i].setVy(((m2 - m1)/totalM)*vy2 + (2*m1/totalM)*vy1);

            return true;
        }
    }
    return false;
}

void MainWindow::paint(QPainter *painter, QPaintEvent) {
    painter->setPen(Qt::black);

    checkCollisionsAndMove();

    for(Ball& b : balls) {
        painter->setBrush(QBrush(Qt::red));
        painter->drawEllipse(b.getPoint(), b.getRadius(), b.getRadius());
        painter->setBrush(Qt::black);
    }

    painter->setBrush(Qt::gray);
    painter->drawRect(board.getRect());
    showInfo(painter);
    board.move();
}

void MainWindow::showInfo(QPainter* painter) {
    painter->drawText(QPointF(0, 10), "Board vx: " + QString::number(board.getVx()));
    painter->drawText(QPointF(0, 20), "Board vy: " + QString::number(board.getVy()));
    painter->drawText(QPointF(0, 30), "Board width: " + QString::number(board.getWidth()));
    painter->drawText(QPointF(0, 40), "Board height: " + QString::number(board.getHeight()));

    for(unsigned long long i = 0; i < balls.size(); ++i) {
        painter->drawText(QPointF(0, 50+10*i), "Ball#" + QString::number(i) + " vx: " + QString::number(balls[i].getVx()));
    }
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);
    paint(&painter, *event);
    painter.end();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_A &&
            board.getX() > 0) {
        board.setVx(-1);
    } else if(event->key() == Qt::Key_D &&
              board.getX() < this->width() - board.getWidth()) {
        board.setVx(1);
    }
//    else if(event->key() == Qt::Key_W) {
//        board.setVy(-4);
//    } else if(event->key() == Qt::Key_S) {
//        board.setVy(4);
//    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)  {
    if((event->key() == Qt::Key_A && board.getVx() < 0) ||
            (event->key() == Qt::Key_D && board.getVx() > 0)) {
        board.setVx(0);
    }
//    if((event->key() == Qt::Key_W && board.getVy() < 0) ||
//            (event->key() == Qt::Key_S && board.getVy() > 0)) {
//        board.setVy(0);
//    }
}

void MainWindow::checkCollisionsAndMove() {
    if(board.getX() < 0) {
        board.setX(0);
        board.setVx(0);
    } else if(board.getX() + board.getWidth() > this->width()) {
        board.setX(this->width() - board.getWidth());
        board.setVx(0);
    }

    for(Ball& b : balls) {
        if(b.getPoint().x() + b.getRadius() >= this->width() ||
                b.getPoint().x() - b.getRadius() <= 0) {
            b.setVx(-b.getVx());
        }
        if(b.getPoint().y() + b.getRadius() >= this->height() ||
                b.getPoint().y() - b.getRadius() <= 0) {
            b.setVy(-b.getVy());
        }

        helper.handleCollision(b, balls);
        helper.handleCollision(board, b);
        b.move();
    }
}