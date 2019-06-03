#include "mainwindow.h"

MainWindow::MainWindow() {
    this->showFullScreen();

    widget = new QGLWidget(this);
    widget->setGeometry(this->geometry());

    map = new Map(widget);
    map->load("map.txt");

    layout = new QGridLayout;
    layout->addWidget(map);
    setLayout(layout);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, map, &Map::animate);
    connect(timer, &QTimer::timeout, this, &MainWindow::gameOver);
    timer->start(5);
}

MainWindow::~MainWindow() {
    delete timer;
    delete layout;
    delete map;
    delete widget;
}

void MainWindow::gameOver() {
    if(!map->gameOver()) {
        return;
    } else if(map->gameOver() > 0) {
//        show win message
    } else if(map->gameOver() < 0) {
//        show lose message
    }
    timer->stop();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    map->keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    map->keyReleaseEvent(event);
}