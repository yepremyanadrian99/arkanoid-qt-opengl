#ifndef DESTROYABLEOBJET_H
#define DESTROYABLEOBJET_H

#include <QtGlobal>

class DestroyableObject {

public:
    DestroyableObject();
    DestroyableObject(qreal);
    ~DestroyableObject();

    qreal getLife() const;
    void setLife(qreal);

private:
    qreal life;

};

#endif // DESTROYABLEOBJET_H