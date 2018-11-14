#include "point.h"

Point::Point(int x, int y) {
    this->_x = x;
    this->_y = y;
}

int Point::x() {
    return this->_x;
}

int Point::y() {
    return this->_y;
}
