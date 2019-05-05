#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QtGlobal>

class GameObject {

public:
    GameObject();
    virtual ~GameObject();

    int getId() const;

private:
    static int nextId;
    int id;

};

#endif // GAMEOBJECT_H