#include "mainwindow.h"

MainWindow::MainWindow(QGLWidget *parent)
    : QGLWidget(parent)
{
    this->setGeometry(100, 100, 800, 600);

    helper = Helper();

    board = Board(20, this->height() - 40, 100, 25);
    board.setVx(0);
    board.setVy(0);

    balls = std::vector<Ball>();

    Ball ball1(100, 150, 20);
    ball1.setVx(3.5);
    ball1.setVy(-1.5);

    Ball ball2(400, 150, 20);
    ball2.setVx(-3.5);
    ball2.setVy(-1.5);

    Ball ball3(300, 150, 20);
    ball3.setVx(-1.0);
    ball3.setVy(-4);

    balls.push_back(ball1);
    balls.push_back(ball2);
    balls.push_back(ball3);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->start(15);
}

MainWindow::~MainWindow()
{
}

void MainWindow::animate()
{
    update();
}

void MainWindow::paint(QPainter *painter, QPaintEvent) {
    painter->setPen(Qt::black);
    for(Ball& b : balls) {
        painter->setBrush(QBrush(Qt::red));
        painter->drawEllipse(b.getPoint(), b.getRadius(), b.getRadius());
        painter->setBrush(Qt::black);
        painter->drawEllipse(b.getPoint(), 3, 3);
        b.move();
        checkCollisions();
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
    if(event->key() == Qt::Key_A) {
        if(board.getX() > 0) {
            board.setVx(-4);
        }
    } else if(event->key() == Qt::Key_D &&
              board.getX() < this->width() - board.getWidth()) {
        board.setVx(4);
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

void MainWindow::checkCollisions() {
    if(board.getX() < 0) {
        board.setX(0);
        board.setVx(0);
    } else if(board.getX() + board.getWidth() > this->width()) {
        board.setX(this->width() - board.getWidth());
        board.setVx(0);
    }
    for(Ball &b : balls) {
        if(b.getPoint().x() + b.getRadius() >= this->width() ||
                b.getPoint().x() - b.getRadius() <= 0) {
            b.setVx(-b.getVx());
        }
        if(b.getPoint().y() + b.getRadius() >= this->height() ||
                b.getPoint().y() - b.getRadius() <= 0) {
            b.setVy(-b.getVy());
        }
        helper.handleCollision(board, b);
    }
}
