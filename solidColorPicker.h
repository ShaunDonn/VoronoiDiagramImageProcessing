/**
 * @file solidColorPicker.h
 * Definition of a solid color picker.
 *
 */
#ifndef SOLIDCOLORPICKER_H
#define SOLIDCOLORPICKER_H

#include "colorPicker.h"
#include "point.h"
#include "center.h"

/**
 * solidColorPicker: a functor that determines the color that should be used
 * given a point p, and simply returning the color of the center.
 *
 */
class solidColorPicker : public colorPicker {
  public:
    /**
     * Constructs a new solidColorPicker.
     *
     */
    solidColorPicker();

    /**
     * Picks the color for point p
    *
     * @param p
     * @return The color of p's center
     */
    virtual HSLAPixel operator()(point p);
};

#endif
