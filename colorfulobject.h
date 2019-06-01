#ifndef COLORFULOBJECT_H
#define COLORFULOBJECT_H

#include <QColor>

class ColorfulObject {

public:
    ColorfulObject();
    ColorfulObject(QColor color);
    ~ColorfulObject();

    const QColor getColor() const;
    void setColor(QColor color);

private:
    QColor color;
};

#endif // COLORFULOBJECT_H