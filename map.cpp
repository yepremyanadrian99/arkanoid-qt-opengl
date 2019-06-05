#include "map.h"

Map::Map(QGLWidget *parent)
    :QGLWidget(parent) {

    this->setGeometry(parent->geometry());

    cellWidth = this->width() / 25;
    cellHeight = this->height() / 30;

    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(51, 0, 102, 255));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    Board::getInstance().setRect(QRectF(this->width() / 2 - cellWidth*3/4, this->height() - cellHeight*3/2, cellWidth*3/2, cellHeight));
    Board::getInstance().setColor(Qt::GlobalColor::white);

    balls = std::vector<Ball*>();

    generateBall();

    loadMedia();
}

Map::~Map() {
    for(size_t i = 0; i < bricks.size(); ++i) {
        delete bricks[i];
    }
    for(size_t i = 0; i < balls.size(); ++i) {
        delete balls[i];
    }
}

void Map::loadMedia() {
    hitMedia.setMedia(QMediaContent(QUrl("qrc:/resources/sounds/hit.wav")));
    destroyMedia.setMedia(QMediaContent(QUrl("qrc:/resources/sounds/destroy.wav")));
    winMedia.setMedia(QMediaContent(QUrl("qrc:/resources/sounds/win.wav")));
    loseMedia.setMedia(QMediaContent(QUrl("qrc:/resources/sounds/lose.wav")));
}

int Map::loadMap(std::string filename) {
    std::stringstream stream;

    QFile file(QString(":/resources/maps/") + QString::fromStdString(filename));
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cout << "Cannot open file: " << filename << std::endl;
        return 0;
    }

    stream.str(QString(file.readAll()).toStdString());
    file.close();

    int i, j, r, g, b, a, life;
    while(stream.peek() != std::stringstream::traits_type::eof()) {
        stream >> i >> j >> r >> g >> b >> a >> life;
        Brick *brick = new Brick(i * cellWidth, j * cellHeight, cellWidth, cellHeight, QColor(r, g, b, a), life);
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
    painter->setPen(Qt::white);

    if(gameOver() != 0) {
        QFont font = painter->font();
        font.setPointSize(100);
        painter->setFont(font);

        QRect center(0, 0, this->width(), this->height());
        QRect bottom(0, 100, this->width(), this->height());

        QString winText("YOU WON");
        QString loseText("YOU LOSE");

        if(gameOver() > 0) {
            painter->drawText(center, winText, QTextOption(Qt::Alignment(Qt::AlignmentFlag::AlignCenter)));
            return;
        } else if(gameOver() < 0) {
            painter->drawText(center, loseText, QTextOption(Qt::Alignment(Qt::AlignmentFlag::AlignCenter)));
            return;
        }
    }

    painter->setPen(Qt::black);

    checkCollisions();

    for(MovableCircle *b : balls) {
        painter->setBrush(dynamic_cast<ColorfulObject*>(b)->getColor());
        painter->drawEllipse(b->getPoint(), b->getRadius(), b->getRadius());
//        painter->drawImage(QRectF(b->getX(), b->getY(), b->getRadius(), b->getRadius()),
//                           QImage(":/resources/images/ball_red.png"));
    }

    for(MovableRectangle *b : bricks) {
        painter->setBrush(dynamic_cast<ColorfulObject*>(b)->getColor());
        painter->drawRect(b->getRect());
//        painter->drawImage(b->getRect(), QImage(QString("%1/board_medium.png").arg(QCoreApplication::applicationDirPath())));
    }

    painter->drawImage(Board::getInstance().getRect(), QImage(":/resources/images/board_large.png"));
//    showInfo(painter);
}

void Map::paintEvent(QPaintEvent *event) {
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);
    paint(&painter, *event);
    painter.end();
}

void Map::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_A &&
            Board::getInstance().getX() > 1) {
        Board::getInstance().setVx(-2);
    } else if(event->key() == Qt::Key_D &&
              Board::getInstance().getX() < this->width() - Board::getInstance().getWidth() - 1) {
        Board::getInstance().setVx(2);
    }
}

void Map::keyReleaseEvent(QKeyEvent *event)  {
    if((event->key() == Qt::Key_A && Board::getInstance().getVx() < 0) ||
            (event->key() == Qt::Key_D && Board::getInstance().getVx() > 0)) {
        Board::getInstance().setVx(0);
    }
}

void Map::showInfo(QPainter* painter) {
    painter->drawText(QPointF(0, 10), "Board vx: " + QString::number(Board::getInstance().getVx()));
    painter->drawText(QPointF(0, 20), "Board vy: " + QString::number(Board::getInstance().getVy()));
    painter->drawText(QPointF(0, 30), "Board x: " + QString::number(Board::getInstance().getX()));
    painter->drawText(QPointF(0, 40), "Board y: " + QString::number(Board::getInstance().getY()));
    painter->drawText(QPointF(0, 50), "Board width: " + QString::number(Board::getInstance().getWidth()));
    painter->drawText(QPointF(0, 60), "Board height: " + QString::number(Board::getInstance().getHeight()));

    painter->setPen(Qt::black);
    for(size_t i = 0; i < balls.size(); ++i) {
        painter->drawText(QPointF(0, 80+10*i*3), "Ball#" + QString::number(i) + " vx: " + QString::number(balls[i]->getVx()));
        painter->drawText(QPointF(0, 90+10*i*3), "Ball#" + QString::number(i) + " vy: " + QString::number(balls[i]->getVy()));
        painter->drawText(QPointF(0, 100+10*i*3), "Ball#" + QString::number(i) + " vx2 + vy2: " + QString::number(balls[i]->getVx()*balls[i]->getVx()+balls[i]->getVy()*balls[i]->getVy()));
    }
}

void Map::checkCollisions() {
    checkBoardCollisionsAndMove();
    checkBallCollisionsAndMove();
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
    for(MovableCircle* b : balls) {
        if(Helper::handleCollision(*b, Board::getInstance())) {
            hitMedia.play();
        }

        for(auto it = bricks.begin(); it != bricks.end(); ) {
            if(Helper::handleCollision(*b, **it)) {
                hitMedia.play();
                (*it)->hit();
                if((*it)->isDestroyed()) {
                    delete *it;
                    it = bricks.erase(it);
                    continue;
                }
            }
            ++it;
        }

        if(b->getPoint().x() + b->getRadius() >= this->width() ||
                b->getPoint().x() - b->getRadius() <= 0) {
            hitMedia.play();
            b->setVx(-b->getVx());
        }
        if(b->getPoint().y() - b->getRadius() <= 0) {
            hitMedia.play();
            b->setVy(-b->getVy());
        }
        if(b->getPoint().y() + b->getRadius() >= this->height()) {
            auto it = std::find_if(balls.begin(), balls.end(), [b](Ball *ball) { return ball->getId() == b->getId(); });
            delete *it;
            balls.erase(it);
            return;
        }

        b->move();
    }
}

void Map::generateBall() {
    std::srand(std::time(NULL));
    qreal vx = (5 + std::rand() % 11) / 10.0;
    qreal vy = std::sqrt(4 - vx * vx);

    Ball *b = new Ball(Board::getInstance().getX() + Board::getInstance().getWidth() / 2, Board::getInstance().getY() - 50, 15);
    b->setVx(vx);
    b->setVy(-abs(vy));
    b->setColor(Qt::red);

    balls.push_back(b);
}