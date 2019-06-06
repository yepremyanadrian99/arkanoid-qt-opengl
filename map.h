#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <sstream>
#include <QGLWidget>
#include <QTimer>
#include <QPaintEvent>
#include <QPalette>
#include <QThread>
#include <QCoreApplication>
#include <QMediaPlayer>
#include "ball.h"
#include "board.h"
#include "helper.h"
#include "brick.h"
#include "constants.h"

using namespace Constants;

class Map : public QGLWidget {

    Q_OBJECT

public slots:
    void animate();

public:
    Map(QGLWidget *parent = nullptr);
    virtual ~Map() override;

    int loadMap(QString filename);
    void loadMedia();
    int gameOver();
    void win();
    void lose();

public:
    void setBackground(QColor color);

public:
    void paintEvent(QPaintEvent *event) override;
    void paint(QPainter *painter, QPaintEvent event);
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    
private:
    void checkCollisions();
    void checkBallCollisionsAndMove();
    void checkBoardCollisionsAndMove();
    void checkRectCollisionsAndMove();
    void checkDestroyedBricks();
    void generateBall();

private:
    std::vector<Ball> balls;
    std::vector<Brick> bricks;
    QMediaPlayer hitMedia;
    QMediaPlayer winMedia;
    QMediaPlayer loseMedia;
    QColor background;
};

#endif // MAP_H
