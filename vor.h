/**
 * @file vor.h
 * Defintion of a vor(onoi) namespace.
 *
 */
#ifndef _VOR_H_
#define _VOR_H_

#include "cs221util/PNG.h"
#include "stack.h"
#include "queue.h"
#include "center.h"
#include "point.h"
#include "animation.h"


#include "dotColorPicker.h"
#include "solidColorPicker.h"
#include "fadeColorPicker.h"
#include <random>
#include <vector>

using namespace cs221util;
using namespace std;

/**
 * filler namespace: specifies a set of functions for creating 
 * artistic effects using voronoi diagrams based on images
 *
 */
namespace filler {
    /**
     * Performs a voronoi fill based on the given image using the color of
     * the centers and employing a depth-first-search approach.
     *
     * @param img The image to be simulated
     * @param double density used to determine the number of centers.
     * @param frameFreq How frequently to add a frame to the animation, in
     *  pixels. For instance, if frameFreq == 1, a frame is added when every
     *  pixel is colored. If frameFreq == 10, a frame is added after every 10
     *  pixels are colored.
     * @return An animation that shows the fill progressing over the image.
     */
    animation vorSolidDFS(PNG &img, double density, int frameFreq);

    /**
     * Performs a voronoi fill based on the given image using the color of
     * the centers and employing a depth-first-search approach. This fill
     * fades the center color using the fade factor, at each level of the
     * algorithm.
     *
     * @param img The image to be simulated
     * @param double density used to determine the number of centers.
     * @param double fade factor used to initialize the fade color picker.
     * @param frameFreq How frequently to add a frame to the animation, in
     *  pixels. For instance, if frameFreq == 1, a frame is added when every
     *  pixel is colored. If frameFreq == 10, a frame is added after every 10
     *  pixels are colored.
     * @return An animation that shows the fill progressing over the image.
     */
    animation vorFadeDFS(PNG &img, double density, double fadeFactor, int frameFreq);


    /**
     * Performs a voronoi fill based on the given image using the color of
     * the centers and employing a breadth-first-search approach.
     *
     * @param img The image to be simulated
     * @param double density used to determine the number of centers.
     * @param frameFreq How frequently to add a frame to the animation, in
     *  pixels. 
     * @return An animation that shows the fill progressing over the image.
     */
    animation vorSolidBFS(PNG &img, double density, int frameFreq);

    /**
     * Performs a voronoi fill based on the given image using the color of
     * the centers and employing a breadth-first-search approach. This fill
     * fades the center color using the fade factor, at each level of the
     * algorithm.
     *
     * @param img The image to be simulated
     * @param double density used to determine the number of centers.
     * @param double fade factor used to initialize the fade color picker.
     * @param frameFreq How frequently to add a frame to the animation, in
     *  pixels. 
     * @return An animation that shows the fill progressing over the image.
     */
    animation vorFadeBFS(PNG &img, double density, double fadeFactor, int frameFreq);

    /* The following two functions are given to you as examples of
     * working fill functions.
    */

    /**
     * Performs a voronoi fill from the given image using a dot pattern,
     * employing a depth-first-search approach.
     *
     * @param img The image to be simulated
     * @param double density
     * @param dotGrid The width of the dot spacing.
     * @param dotSize The radius of the dot.
     * @param frameFreq How frequently to add a frame to the animation, in
     *  pixels. 
     * @return An animation that shows the fill progressing over the image.
     */
    animation vorDotDFS(PNG &img, double density, int dotGrid, int dotSize, int frameFreq);

    /**
     * Performs a voronoi fill from the given image using a dot pattern,
     * employing a breadth-first-search approach.
     *
     * @param img The image to be simulated
     * @param double density
     * @param dotGrid The width of the dot spacing.
     * @param dotSize The radius of the dot.
     * @param frameFreq How frequently to add a frame to the animation, in
     *  pixels. 
     * @return An animation that shows the fill progressing over the image.
     */
    animation vorDotBFS(PNG &img, double density, int dotGrid, int dotSize, int frameFreq);

    vector <center> randSample(PNG &img, double density);


    /**
     * General filling function: a general helper that should be invoked by
     * all of the public fill functions with the appropriate color picker
     * for that type of fill.
     *
     * @param img Image to do the filling on.
     * @param density Determines how many centers to use in the diagram
     * @param fillColor The colorPicker function object to be used for the fill.
     * @param frameFreq How frequently to add a frame to the animation, in
     *  pixels. 
     * @return An animation that shows the fill progressing over the image.
     */
    template<template<class T> class OrderingStructure>
    animation vor(PNG &img, double density, colorPicker &fillColor, int frameFreq);

    double distFromC(point p, int x, int y);
    void processNeighbour(point &currPoint, PNG &canvas, OrderingStructure<point> &currOS, colorPicker &fillColor, int &frameFreq, int &frameTracker, animation &vorResult, vector<vector<bool>> &processTable, int &k);
    bool isValid (point p, int k, int imgW, int imgH, vector<vector<bool>> &processTable, int x, int y);
    void checkFrameTracker(int &frameFreq, animation &vorResult, PNG &img, int &frameTracker);
    void addPixel(point &newPoint, PNG &canvas, colorPicker &fillColor, OrderingStructure<point> &currOS, vector<vector<bool>> &processTable, int &frameTracker, int &frameFreq, animation &vorResult);
    bool duplicate(center &c, vector<center> &centers, int index);

}

#include "vor_given.cpp"
#include "vor.cpp"

#endif