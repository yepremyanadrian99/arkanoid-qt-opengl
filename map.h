#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include <QGLWidget>
#include <QTimer>
#include <QPaintEvent>
#include <QPalette>
#include <QThread>
#include "ball.h"
#include "board.h"
#include "helper.h"
#include "brick.h"

class Map : public QGLWidget {

    Q_OBJECT

public slots:
    void animate();

public:
    Map(QGLWidget *parent = nullptr);
    virtual ~Map() override;

    void load(std::string file);
    int gameOver();

public:
    void paintEvent(QPaintEvent *event) override;
    void paint(QPainter *painter, QPaintEvent event);
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    void checkCollisions();
    void checkBallCollisionsAndMove();
    void checkBoardCollisionsAndMove();
    void checkDestroyedBricks();
    void showInfo(QPainter*);
    void generateBall();

private:
    QTimer *timer;
    Board* board;
    std::vector<Ball*> balls;
    std::vector<Brick*> bricks;
};

#endif // MAP_H
