#include "fadeColorPicker.h"
#include <cmath>

fadeColorPicker::fadeColorPicker(double fade) {
    fadeFactor = fade;
}

HSLAPixel fadeColorPicker::operator()(point p) {
    double centerL = p.c.color.l;
    signed int diffX = p.c.x - p.x;
    signed int diffY = p.c.y - p.y;
    double distSq = sqrt(pow(diffX, 2) + pow(diffY, 2));
    HSLAPixel ret;
    ret.h = p.c.color.h;
    ret.s = p.c.color.s;
    ret.l = centerL * pow(fadeFactor, distSq);
    return ret;
}

