#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGLWidget>
#include <QTimer>
#include <QPaintEvent>
#include "ball.h"
#include "board.h"
#include "helper.h"
#include "brick.h"
#include <QThread>
#include <iostream>

class MainWindow : public QGLWidget {

    Q_OBJECT

public slots:
    void animate();

public:
    MainWindow(QGLWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    void paint(QPainter *painter, QPaintEvent event);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    void checkCollisions();
    void checkBallCollisionsAndMove();
    void checkBoardCollisionsAndMove();
    void showInfo(QPainter*);
    void generateBall();

private:
    int time = 50;
    QTimer *timer;
    Board* board;
    std::vector<MovableCircle*> balls;
    std::vector<MovableRectangle*> bricks;
};

#endif // MAINWINDOW_H