#include "mainwindow.h"

MainWindow::MainWindow() {
    this->showFullScreen();

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::black);

    widget = new QGLWidget(this);
    widget->setGeometry(this->geometry());
    widget->setPalette(pal);

    this->setPalette(pal);

    map = new Map(widget);
    if(!map->loadMap("map1.txt")) {
        return;
    }

    layout = new QGridLayout;
    layout->addWidget(map);
    setLayout(layout);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, map, &Map::animate);
    connect(timer, &QTimer::timeout, this, &MainWindow::gameOver);
    timer->start(1);
}

MainWindow::~MainWindow() {
    delete timer;
    delete layout;
    delete map;
    delete widget;
}

void MainWindow::gameOver() {
    if(map->gameOver()) {
        timer->stop();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    map->keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    map->keyReleaseEvent(event);
}