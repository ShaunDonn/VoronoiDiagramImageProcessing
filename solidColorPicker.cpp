#include "solidColorPicker.h"

solidColorPicker::solidColorPicker() {}

HSLAPixel solidColorPicker::operator()(point p) {
    HSLAPixel ret;
    ret.h = p.c.color.h;
    ret.s = p.c.color.s;
    ret.l = p.c.color.l;
    return ret;
}
