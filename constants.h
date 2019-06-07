#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QColor>
#include <QMediaContent>
#include <QRectF>
#include <QImage>

using std::string;

namespace Constants {
    static const QColor BACKGROUND_RGB = QColor(45, 45, 45, 255);
    static const QColor BORDER_RGB = Qt::black;
    static const QString LOAD_MAP = "map1.txt";
    static const int TIMER_SPEED = 1;
    static const qreal SCREEN_WIDTH = 1920;
    static const qreal SCREEN_HEIGHT = 1080;
    static const qreal CELL_HORIZONTAL_COUNT = 25;
    static const qreal CELL_VERTICAL_COUNT = 25;
    static const qreal CELL_WIDTH = SCREEN_WIDTH / CELL_HORIZONTAL_COUNT;
    static const qreal CELL_HEIGHT = SCREEN_HEIGHT / CELL_VERTICAL_COUNT;
    static const int BOARD_ID = 0;
    static const qreal BOARD_WIDTH = CELL_WIDTH*3/2;
    static const qreal BOARD_HEIGHT = CELL_HEIGHT;
    static const qreal BOARD_STARTING_X = SCREEN_WIDTH / 2 - BOARD_WIDTH / 2;
    static const qreal BOARD_STARTING_Y = SCREEN_HEIGHT - BOARD_HEIGHT;
    static const qreal BOARD_VELOCITY_X = 2;
    static const QImage BOARD_LARGE_IMAGE = QImage(":/resources/images/board_large.png");
    static const QImage BOARD_MEDIUM_IMAGE = QImage(":/resources/images/board_medium.png");
    static const QImage BOARD_SMALL_IMAGE = QImage(":/resources/images/board_small.png");
    static const qreal BALL_RADIUS = 15;
    static const qreal BALL_STARTING_X = BOARD_STARTING_X + BOARD_WIDTH / 2;
    static const qreal BALL_STARTING_Y = BOARD_STARTING_Y - BALL_RADIUS * 2;
    static const qreal BALL_VELOCITY = 4;
    static const qreal BALL_VELOCITY_X_Y_MIN = 0.5;
    static const QColor BALL_COLOR = Qt::white;
    static const qreal BRICK_SPEED = 0.5;
    static const qreal BRICK_LEFT_SCREEN_BORDER = SCREEN_WIDTH / 4;
    static const qreal BRICK_RIGHT_SCREEN_BORDER = SCREEN_WIDTH - SCREEN_WIDTH / 8;
    static const QUrl HIT_SOUND_RESOURCE_URL = QUrl("qrc:/resources/sounds/hit.wav");
    static const QUrl DESTROY_SOUND_RESOURCE_URL = QUrl("qrc:/resources/sounds/destroy.wav");
    static const QUrl WIN_SOUND_RESOURCE_URL = QUrl("qrc:/resources/sounds/win.wav");
    static const QUrl LOSE_SOUND_RESOURCE_URL = QUrl("qrc:/resources/sounds/lose.wav");
    static const QString MAPS_RESOURCE_PATH = ":/resources/maps/";
    static const std::string CANNOT_OPEN_FILE_MSG = "Cannot open file: ";
    static const QRectF GAME_OVER_MSG_RECT = QRectF(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    static const QColor GAME_OVER_MSG_COLOR = Qt::white;
    static const int GAME_OVER_MSG_FONT_POINT_SIZE = 100;
    static const QString WIN_MSG = "YOU WON";
    static const QString LOSE_MSG = "YOU LOSE";
    static const QColor NORMAL_PEN_COLOR = Qt::black;
    static const Qt::Key MOVE_LEFT_KEY1 = Qt::Key_A;
    static const Qt::Key MOVE_LEFT_KEY2 = Qt::Key_Left;
    static const Qt::Key MOVE_RIGHT_KEY1 = Qt::Key_D;
    static const Qt::Key MOVE_RIGHT_KEY2 = Qt::Key_Right;
    static const int IGNORE_BOARD_COUNT = 100;
}

#endif // CONSTANTS_H
