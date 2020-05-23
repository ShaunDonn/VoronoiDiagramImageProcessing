#include "customColorPicker.h"

customColorPicker::customColorPicker() {
}

HSLAPixel customColorPicker::operator()(point p) {
    double l;
    if ((p.x % 20 < 10) && (p.y % 20 < 10)) {
        l = 100 - p.c.color.l;
    } else {
        l = p.c.color.l;
    }
    HSLAPixel ret;
    ret.l = l;
    ret.s = p.c.color.s;
    ret.h = p.c.color.h;
    ret.a = p.c.color.a;
    return ret;
}