#include "mainwindow.h"

MainWindow::MainWindow() {
    this->showFullScreen();

    widget = new QGLWidget(this);
    widget->setGeometry(this->geometry());
    map = new Map(widget);

    layout = new QGridLayout;
    layout->addWidget(map);
    setLayout(layout);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, map, &Map::animate);
    timer->start(5);
}

MainWindow::~MainWindow() {
    delete map;
    delete widget;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    map->keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    map->keyReleaseEvent(event);
}