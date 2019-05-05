#ifndef COLORFULOBJECT_H
#define COLORFULOBJECT_H

#include <QColor>

class ColorfulObject {

public:
    ColorfulObject();
    ColorfulObject(QColor);
    ~ColorfulObject();

    const QColor getColor() const;
    void setColor(QColor);

private:
    QColor color;

};

#endif // COLORFULOBJECT_H