#include "map.h"

Map::Map(QGLWidget *parent)
    :QGLWidget(parent) {

    this->setGeometry(parent->geometry());
    Board::getInstance().setRect(QRectF(BOARD_STARTING_X, BOARD_STARTING_Y, BOARD_WIDTH, BOARD_HEIGHT));
    generateBall();
    loadMedia();
}

Map::~Map() {
}

void Map::setBackground(QColor color) {
    QPalette pal = palette();
    pal.setColor(QPalette::Background, color);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

void Map::loadMedia() {
    hitMedia.setMedia(QMediaContent(HIT_SOUND_RESOURCE_URL));
    winMedia.setMedia(QMediaContent(WIN_SOUND_RESOURCE_URL));
    loseMedia.setMedia(QMediaContent(LOSE_SOUND_RESOURCE_URL));
}

int Map::loadMap(QString filename) {
    std::stringstream stream;

    QFile file(QString(MAPS_RESOURCE_PATH + filename));
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cout << CANNOT_OPEN_FILE_MSG << filename.toStdString() << std::endl;
        return 0;
    }

    stream.str(QString(file.readAll()).toStdString());
    file.close();

    int i, j, r, g, b, a, life;
    bool isMovable;
    while(stream.peek() != std::stringstream::traits_type::eof()) {
        stream >> i >> j >> r >> g >> b >> a >> life >> isMovable;
        Brick brick(i * CELL_WIDTH, j * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, QColor(r, g, b, a), life);
        if(isMovable) {
            brick.setVx(BRICK_SPEED);
        }
        bricks.push_back(brick);
    }
    return 1;
}

int Map::gameOver() {
    if(bricks.empty()) {
        winMedia.play();
        return 1;
    } else if(balls.empty()) {
        loseMedia.play();
        return -1;
    }
    return 0;
}

void Map::animate() {
    update();
}

void Map::paint(QPainter *painter, QPaintEvent) {
    if(gameOver() != 0) {
        painter->setPen(GAME_OVER_MSG_COLOR);

        QFont font = painter->font();
        font.setPointSize(GAME_OVER_MSG_FONT_POINT_SIZE);
        painter->setFont(font);

        if(gameOver() > 0) {
            painter->drawText(GAME_OVER_MSG_RECT, WIN_MSG, QTextOption(Qt::Alignment(Qt::AlignmentFlag::AlignCenter)));
            return;
        } else if(gameOver() < 0) {
            painter->drawText(GAME_OVER_MSG_RECT, LOSE_MSG, QTextOption(Qt::Alignment(Qt::AlignmentFlag::AlignCenter)));
            return;
        }
    }

    painter->setPen(NORMAL_PEN_COLOR);

    checkCollisions();

    for(Ball &b : balls) {
        painter->setBrush(b.getColor());
        painter->drawEllipse(b.getPoint(), b.getRadius(), b.getRadius());
    }

    for(Brick &b : bricks) {
        painter->setBrush(b.getColor());
        painter->drawRect(b.getRect());
    }

    painter->drawImage(Board::getInstance().getRect(), BOARD_MEDIUM_IMAGE);
}

void Map::paintEvent(QPaintEvent *event) {
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);
    painter.setRenderHint(QPainter::RenderHint::HighQualityAntialiasing);
    paint(&painter, *event);
    painter.end();
}

void Map::keyPressEvent(QKeyEvent *event) {
    if((event->key() == MOVE_LEFT_KEY1 || event->key() == MOVE_LEFT_KEY2) &&
            Board::getInstance().getX() > 1) {
        Board::getInstance().setVx(-BOARD_VELOCITY_X);
    } else if((event->key() == MOVE_RIGHT_KEY1 || event->key() == MOVE_RIGHT_KEY2) &&
              Board::getInstance().getX() < this->width() - Board::getInstance().getWidth() - 1) {
        Board::getInstance().setVx(BOARD_VELOCITY_X);
    }
}

void Map::keyReleaseEvent(QKeyEvent *event)  {
    if(((event->key() == MOVE_LEFT_KEY1 || event->key() == MOVE_LEFT_KEY2) && Board::getInstance().getVx() < 0) ||
            ((event->key() == MOVE_RIGHT_KEY1 || event->key() == MOVE_RIGHT_KEY2) && Board::getInstance().getVx() > 0)) {
        Board::getInstance().setVx(0);
    }
}

void Map::checkCollisions() {
    checkBoardCollisionsAndMove();
    checkBallCollisionsAndMove();
    checkRectCollisionsAndMove();
}

void Map::checkBoardCollisionsAndMove() {
    Board::getInstance().move();
    if(Board::getInstance().getX() < 1) {
        Board::getInstance().setX(1);
    } else if(Board::getInstance().getX() + Board::getInstance().getWidth() >= this->width()) {
        Board::getInstance().setX(this->width() - Board::getInstance().getWidth());
    }
}

void Map::checkBallCollisionsAndMove() {
    for(Ball &b : balls) {
        if(Helper::handleCollision(b, Board::getInstance())) {
            hitMedia.play();
        }

        for(auto it = bricks.begin(); it != bricks.end(); ) {
            it->move();
            if(Helper::handleCollision(b, *it)) {
                hitMedia.play();
                it->hit();
                if(it->isDestroyed()) {
                    it = bricks.erase(it);
                    continue;
                }
            }
            ++it;
        }

        if(b.getPoint().x() + b.getRadius() >= this->width() ||
                b.getPoint().x() - b.getRadius() <= 0) {
            hitMedia.play();
            b.getVelocity().reverseX();
        }
        if(b.getPoint().y() - b.getRadius() <= 0) {
            hitMedia.play();
            b.getVelocity().reverseY();
        }
        if(b.getPoint().y() + b.getRadius() >= this->height()) {
            auto it = std::find_if(balls.begin(), balls.end(), [b](Ball &ball) { return ball.getId() == b.getId(); });
            balls.erase(it);
            return;
        }

        b.move();
    }
}

void Map::checkRectCollisionsAndMove() {
    for(Brick &b : bricks) {
        if(abs(b.getVx()) > 0.0 || abs(b.getVy()) > 0.0) {
            if(b.getX() <= BRICK_LEFT_SCREEN_BORDER ||
                    b.getX() + b.getWidth() >= BRICK_RIGHT_SCREEN_BORDER) {
                b.getVelocity().reverseX();
            }
        }
    }
}

void Map::generateBall() {
    std::srand(std::time(NULL));
    qreal vx = (BALL_VELOCITY_X_Y_MIN*10 + std::rand() % int(BALL_VELOCITY*BALL_VELOCITY) - BALL_VELOCITY_X_Y_MIN*10) / 10.0;
    qreal vy = std::sqrt(BALL_VELOCITY - vx * vx);

    Ball b(BALL_STARTING_X, BALL_STARTING_Y, BALL_RADIUS);
    b.setVx(vx);
    b.setVy(-abs(vy));
    b.setColor(BALL_COLOR);

    balls.push_back(b);
}