#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QFile>
#include <iostream>
#include "map.h"
#include "constants.h"

using namespace Constants;

class MainWindow : public QWidget {

    Q_OBJECT

public:
    MainWindow();
    ~MainWindow() override;

    void gameOver();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    Map *map;
    QGLWidget *widget;
    QGridLayout *layout;
    QTimer *timer;
};

#endif // MAINWINDOW_H