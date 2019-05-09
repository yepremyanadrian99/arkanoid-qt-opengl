#include "mainwindow.h"

MainWindow::MainWindow(QGLWidget *parent)
    : QGLWidget(parent) {

    this->setGeometry(100, 100, 800, 600);
    this->updateGL();

    helper = Helper();

    board = new Board(this->width() - 200, this->height() - 25, 100, 25);
    board->setVx(0);
    board->setVy(0);

    balls = std::vector<MovableCircle*>();

//    qreal ballWidth = 10;

//    Ball *ball1 = new Ball(100, 300, ballWidth);
//    ball1->setVx(-5.5);
//    ball1->setVy(0.5);

//    Ball *ball2 = new Ball(400, 200, ballWidth);
//    ball2->setVx(-6.25);
//    ball2->setVy(-0.75);

//    Ball *ball3 = new Ball(300, 250, ballWidth);
//    ball3->setVx(1);
//    ball3->setVy(-5.80);

//    Ball *ball4 = new Ball(200, 200, ballWidth);
//    ball4->setVx(2);
//    ball4->setVy(-4.5);

//    Ball *ball5 = new Ball(400, 250, ballWidth);
//    ball5->setVx(-1.25);
//    ball5->setVy(-0.75);

//    Ball *ball6 = new Ball(300, 350, ballWidth);
//    ball6->setVx(1);
//    ball6->setVy(-0.80);

//    Ball *ball7 = new Ball(200, 300, ballWidth);
//    ball7->setVx(0.5);
//    ball7->setVy(-0.5);

//    Ball *ball8 = new Ball(400, 100, ballWidth);
//    ball8->setVx(-0.25);
//    ball8->setVy(-0.75);

//    Ball *ball9 = new Ball(300, 150, ballWidth);
//    ball9->setVx(0.20);
//    ball9->setVy(-0.80);

//    balls.push_back(ball1);
//    balls.push_back(ball2);
//    balls.push_back(ball3);
//    balls.push_back(ball4);
//    balls.push_back(ball5);
//    balls.push_back(ball6);
//    balls.push_back(ball7);
//    balls.push_back(ball8);
//    balls.push_back(ball9);

    generateBall();

    for(int i = 1; i * 5 < this->width(); ++i) {
        bricks.push_back(new Brick(i * 100 + 50, 50, 50, 25));
    }

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->start(1);
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
    }

    for(MovableRectangle *b : bricks) {
        painter->setBrush(dynamic_cast<ColorfulObject*>(b)->getColor());
        painter->drawRect(b->getRect());
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
            board->getX() > 0) {
        board->setVx(-4);
    } else if(event->key() == Qt::Key_D &&
              board->getX() < this->width() - board->getWidth()) {
        board->setVx(4);
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
    painter->drawText(QPointF(0, 30), "Board width: " + QString::number(board->getWidth()));
    painter->drawText(QPointF(0, 40), "Board height: " + QString::number(board->getHeight()));

    for(size_t i = 0; i < balls.size(); ++i) {
        painter->drawText(QPointF(0, 50+10*i), "Ball#" + QString::number(i) + " vx: " + QString::number(balls[i]->getVx()));
        painter->drawText(QPointF(0, 100+10*i), "Ball#" + QString::number(i) + " vy: " + QString::number(balls[i]->getVy()));
        painter->drawText(QPointF(0, 150+10*i), "Ball#" + QString::number(i) + " vx2 + vy2: " + QString::number(balls[i]->getVx()*balls[i]->getVx()+balls[i]->getVy()*balls[i]->getVy()));
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
        board->setVx(0);
    } else if(board->getX() + board->getWidth() > this->width() - 1) {
        board->setX(this->width() - board->getWidth() - 1);
        board->setVx(0);
    }
}

void MainWindow::checkBallCollisionsAndMove() {
    for(MovableCircle* b : balls) {
        helper.handleCollision(*b, balls);
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
    std::srand(time(NULL));
    qreal vx = (5 + std::rand() % 31) / 10.0;
    qreal vy = std::sqrt(16 - vx * vx);

    Ball *b = new Ball(board->getX() + board->getWidth() / 2, board->getY() - 50, 10);
    b->setVx(vx);
    b->setVy(vy);

    balls.push_back(b);
}
