#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <iostream>
#include "map.h"

class MainWindow : public QWidget {

    Q_OBJECT

public:
    MainWindow();
    ~MainWindow() override;

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