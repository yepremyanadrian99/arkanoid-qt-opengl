#ifndef COLORFULOBJECT_H
#define COLORFULOBJECT_H

#include <QColor>

class ColorfulObject {

public:
    ColorfulObject();
    ColorfulObject(QColor color);
    virtual ~ColorfulObject() = 0;

    const QColor getColor() const;
    void setColor(QColor color);

private:
    QColor color;
};

#endif // COLORFULOBJECT_H