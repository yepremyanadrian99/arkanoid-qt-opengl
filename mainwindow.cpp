#include "mainwindow.h"
#include <QCoreApplication>
#include <iostream>

MainWindow::MainWindow(QGLWidget *parent)
    : QGLWidget(parent) {

    this->setGeometry(100, 100, 800, 600);
    this->updateGL();

    helper = Helper();
    board = new Board(this->width() - 90, this->height() - 25, 80, 25);
    balls = std::vector<MovableCircle*>();

    for(int i = 0; i < 10; ++i) {
        generateBall();
    }

//    balls[0]->setX(40);
//    balls[1]->setX(70);
//    balls[2]->setX(100);
    balls[3]->setX(130);
//    balls[4]->setX(160);
//    balls[5]->setX(190);
//    balls[6]->setX(220);
//    balls[7]->setX(250);
//    balls[8]->setX(280);
//    balls[9]->setX(310);

    board->setVx(-2);

    for(int i = 1; 50 + 75 * i < this->width(); ++i) {
        bricks.push_back(new Brick(50 + 75 * i, 50, 50, 25));
    }

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->start(time);
}

MainWindow::~MainWindow() {}

void MainWindow::animate() {
    update();
}

void MainWindow::paint(QPainter *painter, QPaintEvent) {
    painter->setPen(Qt::blue);

    checkCollisions();

    for(MovableCircle *b : balls) {
        painter->setBrush(dynamic_cast<ColorfulObject*>(b)->getColor());
        painter->drawEllipse(b->getPoint(), b->getRadius(), b->getRadius());
//        painter->drawImage(QRectF(b->getX() - b->getRadius(), b->getY() - b->getRadius(), b->getRadius() * 2, b->getRadius() * 2),
//                           QImage(QString("%1/ball_red.png").arg(QCoreApplication::applicationDirPath())));
    }

    for(MovableRectangle *b : bricks) {
        painter->setBrush(dynamic_cast<ColorfulObject*>(b)->getColor());
        painter->drawRect(b->getRect());
//        painter->drawImage(b->getRect(), QImage(QString("%1/board_medium.png").arg(QCoreApplication::applicationDirPath())));
    }

    painter->setBrush(dynamic_cast<ColorfulObject*>(board)->getColor());
    painter->drawRect(board->getRect());

    showInfo(painter);
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
            board->getX() > 1) {
        board->setVx(-2);
    } else if(event->key() == Qt::Key_D &&
              board->getX() < this->width() - board->getWidth() - 1) {
        board->setVx(2);
    } else if(event->key() == Qt::Key_F) {
        if(time == 150) {
            time = 1;
        } else {
            time = 150;
        }
        timer->stop();
        timer->start(time);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)  {
    if((event->key() == Qt::Key_A && board->getVx() < 0) ||
            (event->key() == Qt::Key_D && board->getVx() > 0)) {
        board->setVx(0);
    }
}

void MainWindow::showInfo(QPainter* painter) {
    painter->drawText(QPointF(0, 10), "Board vx: " + QString::number(board->getVx()));
    painter->drawText(QPointF(0, 20), "Board vy: " + QString::number(board->getVy()));
    painter->drawText(QPointF(0, 30), "Board x: " + QString::number(board->getX()));
    painter->drawText(QPointF(0, 40), "Board y: " + QString::number(board->getY()));
    painter->drawText(QPointF(0, 50), "Board width: " + QString::number(board->getWidth()));
    painter->drawText(QPointF(0, 60), "Board height: " + QString::number(board->getHeight()));

    painter->setPen(Qt::black);
    for(size_t i = 0; i < balls.size(); ++i) {
        painter->drawText(QPointF(0, 80+10*i*3), "Ball#" + QString::number(i) + " vx: " + QString::number(balls[i]->getVx()));
        painter->drawText(QPointF(0, 90+10*i*3), "Ball#" + QString::number(i) + " vy: " + QString::number(balls[i]->getVy()));
        painter->drawText(QPointF(0, 100+10*i*3), "Ball#" + QString::number(i) + " vx2 + vy2: " + QString::number(balls[i]->getVx()*balls[i]->getVx()+balls[i]->getVy()*balls[i]->getVy()));
    }
}

void MainWindow::checkCollisions() {
    checkBoardCollisionsAndMove();
    checkBallCollisionsAndMove();
}

void MainWindow::checkBoardCollisionsAndMove() {
    board->move();
    if(board->getX() < 1) {
        board->setX(1);
    } else if(board->getX() + board->getWidth() >= this->width()) {
        board->setX(this->width() - board->getWidth());
    }
}

void MainWindow::checkBallCollisionsAndMove() {
    for(MovableCircle* b : balls) {
        helper.handleCollision(*b, *board);
        helper.handleCollision(*b, bricks);

        if(b->getPoint().x() + b->getRadius() >= this->width() ||
                b->getPoint().x() - b->getRadius() <= 0) {
            b->setVx(-b->getVx());
        }
        if(b->getPoint().y() + b->getRadius() >= this->height() ||
                b->getPoint().y() - b->getRadius() <= 0) {
            b->setVy(-b->getVy());
        }

        b->move();
    }
}

void MainWindow::generateBall() {
    std::srand(std::time(NULL));
    qreal vx = 1.9;
//    qreal vx = (5 + std::rand() % 11) / 10.0;
    qreal vy = std::sqrt(4 - vx * vx);

    Ball *b = new Ball(board->getX() + board->getWidth() / 2, board->getY() - 50, 10);
    b->setVx(vx);
    b->setVy(vy);

    balls.push_back(b);
}