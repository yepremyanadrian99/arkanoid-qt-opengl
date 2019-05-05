#include "colorfulobject.h"

ColorfulObject::ColorfulObject() {
}

ColorfulObject::ColorfulObject(QColor color)
    :color(color) {
}

ColorfulObject::~ColorfulObject() {
}

const QColor ColorfulObject::getColor() const {
    return this->color;
}

void ColorfulObject::setColor(QColor color) {
    this->color = color;
}