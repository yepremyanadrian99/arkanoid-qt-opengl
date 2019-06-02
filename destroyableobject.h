#ifndef DESTROYABLEOBJET_H
#define DESTROYABLEOBJET_H

#include <QtGlobal>

class DestroyableObject {

public:
    DestroyableObject();
    DestroyableObject(qreal life);
    ~DestroyableObject();

    qreal getLife() const;
    void setLife(qreal life);
    void hit();
    bool isDestroyed() const;

private:
    qreal life;
};

#endif // DESTROYABLEOBJET_H