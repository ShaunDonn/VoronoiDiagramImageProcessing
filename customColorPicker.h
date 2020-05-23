/**
 * @file customColorPicker.h
 * Definition of a custom color picker.
 *
 */
#ifndef CUSTOMCOLORPICKER_H
#define CUSTOMCOLORPICKER_H

#include "colorPicker.h"
#include "point.h"
#include "center.h"

/**
 * customColor
 *Picker: a functor that determines the color that should be used
 * given an x and a y coordinate using a grid pattern of modified luminance.
 *
 */
class customColorPicker : public colorPicker {
public:

    customColorPicker();

    virtual HSLAPixel operator()(point p);

};

#endif