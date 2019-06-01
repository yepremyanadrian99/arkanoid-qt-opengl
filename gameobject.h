#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QtGlobal>

class GameObject {

public:
    GameObject();
    virtual ~GameObject();

    int getId() const;

private:
    int id;
    static int nextId;
    static int getNextId();
};

#endif // GAMEOBJECT_H