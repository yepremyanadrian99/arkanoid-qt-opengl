#include "mainwindow.h"

MainWindow::MainWindow() {
    this->showFullScreen();

    QPalette pal = palette();
    pal.setColor(QPalette::Background, BORDER_RGB);

    widget = new QGLWidget(this);
    widget->setGeometry(this->geometry());
    widget->setPalette(pal);

    this->setPalette(pal);

    map = new Map(widget);
    if(!map->loadMap(LOAD_MAP)) {
        return;
    }
    map->setBackground(BACKGROUND_RGB);

    layout = new QGridLayout;
    layout->addWidget(map);
    setLayout(layout);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, map, &Map::animate);
    connect(timer, &QTimer::timeout, this, &MainWindow::gameOver);
    timer->start(TIMER_SPEED);
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