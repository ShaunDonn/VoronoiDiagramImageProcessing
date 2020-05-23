/**
 * @file vor.cpp
 * Implementation of functions in the filler namespace. 
 *
 */

animation filler::vorDotDFS(PNG &img, double density, int dotGrid, int dotSize, int frameFreq) {
    dotColorPicker a(dotGrid, dotSize);
    return vor<Stack>(img, density, a, frameFreq);
}

animation filler::vorSolidDFS(PNG &img, double density, int frameFreq) {
    solidColorPicker a;
    return vor<Stack>(img, density, a, frameFreq);
}

animation filler::vorFadeDFS(PNG &img, double density, double fadeFactor, int frameFreq) {
    fadeColorPicker a(fadeFactor);
    return vor<Stack>(img, density, a, frameFreq);
}

animation filler::vorDotBFS(PNG &img, double density, int dotGrid, int dotSize, int frameFreq) {
    dotColorPicker a(dotGrid, dotSize);
    return vor<Queue>(img, density, a, frameFreq);
}

animation filler::vorSolidBFS(PNG &img, double density, int frameFreq) {
    solidColorPicker a;
    return vor<Queue>(img, density, a, frameFreq);
}

animation filler::vorFadeBFS(PNG &img, double density, double fadeFactor, int frameFreq) {
    fadeColorPicker a(fadeFactor);
    return vor<Queue>(img, density, a, frameFreq);
}


template<template<class T> class OrderingStructure>
animation filler::vor(PNG &img, double density, colorPicker &fillColor, int frameFreq) {     
 animation vorResult;//animation that will be returned (becomes gif)
 PNG canvas = PNG(img.width(), img.height());

 vector<vector<bool>> processTable;//a 2D vector of booleans (stores the processed status of each point in image)
 int frameTracker = 0;//tracks how many points have been processed
 for(unsigned int m = 0; m < img.width();m++){//initialize processTable to have the same dimensions as the image
     vector<bool> tempBoolList;//
     for(unsigned int n = 0; n < img.height(); n++){
         tempBoolList.push_back(false);
     }
     processTable.push_back(tempBoolList);
 }
    vector<center> centers = randSample(img, density);//VECTOR OF CENTERS
    
    vector<OrderingStructure<point>> OSlist;//vector of ordering structures (either stacks or queues) of points

    for (unsigned long i = 0; i < centers.size(); i++){
        if(!duplicate(centers[i], centers, i)){
            HSLAPixel* currPixel = canvas.getPixel(centers[i].x, centers[i].y);
            OrderingStructure<point> newOS; //OS of points
            point newPoint = point(centers[i]);
            *currPixel = fillColor(newPoint);
            newOS.add(point(centers[i])); //adds center (in point form) as first element in Queue - will need to calculate colour of future points by executing a() on each one (with their center set to the right center)
            OSlist.push_back(newOS); //adds the Ordering Structure of points (currently only center) to centerQs list
            processTable[centers[i].x][centers[i].y] = true;
            frameTracker++;
            checkFrameTracker(frameFreq, vorResult, canvas, frameTracker);
        }
    }
    //performing fill
    int emptyCount = 0;
    int Vsize = OSlist.size();
    int count = 0; //iterator through pointQs
    int k = 0; //this will keep track of what level we are on
    vector<bool> OSisEmpty;
    for(int b = 0; b < Vsize; b++){
        OSisEmpty.push_back(false);
    }
    int kVal;
    while (emptyCount < Vsize){//loop until all OS in the vector are empty
        if(!OSisEmpty[count]){//if the OS at that position is not empty
            point currPoint = OSlist[count].peek();//checks next point in the OS
            k = currPoint.level;
            while(currPoint.level == k){
                currPoint = OSlist[count].remove();//pops point off stack (its level == k)
                processNeighbour(currPoint, canvas, OSlist[count], fillColor, frameFreq, frameTracker, vorResult, processTable, k);
                if(OSlist[count].isEmpty()){
                    OSisEmpty[count] = true;//marks that OS as empty now
                    emptyCount++;
                    break; //break out of this while loop if the OS is now empty
                }
                currPoint = OSlist[count].peek();
            } 
        }
        if(count < Vsize-1){//to continue iterating through vector of OS
            count++;
        }else{//if you reach the end of the vector, go back to the start and iterate again
            count = 0;
        }
    }  

    vorResult.addFrame(canvas);
    return vorResult; 
}

bool filler::duplicate(center &c, vector<center> &centers, int index){
    for(int i = 0; i<index; i++){
        if(centers[i].x == c.x && centers[i].y == c.y){
            return true;
        }
    }
    return false;
}

double filler::distFromC(point p, int x, int y){//finds Euclidean distance of point from its center
    signed int diffx = p.c.x-x;
    signed int diffy = p.c.y-y;
    double dist = sqrt((diffx*diffx)+(diffy*diffy));
    return dist;
}

void filler::processNeighbour(point &currPoint, PNG &canvas, OrderingStructure<point> &currOS, colorPicker &fillColor, int &frameFreq, int &frameTracker, animation &vorResult, vector<vector<bool>> &processTable, int &k){
    unsigned int imageWidth = canvas.width();
    unsigned int imageHeight = canvas.height();
    if(isValid(currPoint, k+1, imageWidth, imageHeight, processTable, currPoint.x, currPoint.y-1)){//N
        point newPoint = point(currPoint.x, currPoint.y-1,currPoint.c, k+1);
        addPixel(newPoint, canvas, fillColor, currOS, processTable, frameTracker, frameFreq, vorResult);
    }
    if(isValid(currPoint, k+1, imageWidth, imageHeight, processTable, currPoint.x-1, currPoint.y-1)){//NW
        point newPoint = point(currPoint.x-1, currPoint.y-1,currPoint.c, k+1);
        addPixel(newPoint, canvas, fillColor, currOS, processTable, frameTracker, frameFreq, vorResult);
    }
    if(isValid(currPoint, k+1, imageWidth, imageHeight, processTable, currPoint.x-1, currPoint.y)){//W
        point newPoint = point(currPoint.x-1, currPoint.y,currPoint.c, k+1);
        addPixel(newPoint, canvas, fillColor, currOS, processTable, frameTracker, frameFreq, vorResult);
    }
    if(isValid(currPoint, k+1, imageWidth, imageHeight, processTable, currPoint.x-1, currPoint.y+1)){//SW
        point newPoint = point(currPoint.x-1, currPoint.y+1,currPoint.c, k+1);
        addPixel(newPoint, canvas, fillColor, currOS, processTable, frameTracker, frameFreq, vorResult);
    }
    if(isValid(currPoint, k+1, imageWidth, imageHeight, processTable, currPoint.x, currPoint.y+1)){//S
       point newPoint = point(currPoint.x, currPoint.y+1,currPoint.c, k+1);
       addPixel(newPoint, canvas, fillColor, currOS, processTable, frameTracker, frameFreq, vorResult);
    }
    if(isValid(currPoint, k+1, imageWidth, imageHeight, processTable, currPoint.x+1, currPoint.y+1)){//SE
       point newPoint = point(currPoint.x+1, currPoint.y+1,currPoint.c, k+1);
       addPixel(newPoint, canvas, fillColor, currOS, processTable, frameTracker, frameFreq, vorResult);
    }
    if(isValid(currPoint, k+1, imageWidth, imageHeight, processTable, currPoint.x+1, currPoint.y)){//E
        point newPoint = point(currPoint.x+1, currPoint.y,currPoint.c, k+1);
        addPixel(newPoint, canvas, fillColor, currOS, processTable, frameTracker, frameFreq, vorResult);
    }
    if(isValid(currPoint, k+1, imageWidth, imageHeight, processTable, currPoint.x+1, currPoint.y-1)){//NE
        point newPoint = point(currPoint.x+1, currPoint.y-1,currPoint.c, k+1);
        addPixel(newPoint, canvas, fillColor, currOS, processTable, frameTracker, frameFreq, vorResult);
    }
}

void filler::addPixel(point &newPoint, PNG &canvas, colorPicker &fillColor, OrderingStructure<point> &currOS, vector<vector<bool>> &processTable, int &frameTracker, int &frameFreq, animation &vorResult){
    HSLAPixel* newPixel = canvas.getPixel(newPoint.x, newPoint.y);
    *newPixel = fillColor(newPoint);
    currOS.add(newPoint);
    processTable[newPoint.x][newPoint.y] = true;
    frameTracker++;
    checkFrameTracker(frameFreq, vorResult, canvas, frameTracker);
}

bool filler::isValid(point p, int k, int imgW, int imgH, vector<vector<bool>> &processTable, int x, int y){
    if (distFromC(p, x, y) <= k){
        if (x < imgW && x >= 0 && y < imgH && y >= 0){
            if(!processTable[x][y]){
                return true;
            }
        }
    }
    return false;
}

void filler::checkFrameTracker(int &frameFreq, animation &vorResult, PNG &img, int &frameTracker){//checks if the frameTracker is a multiple of the frameFrequency, if it is, it adds this image to the gif
    if((frameTracker % frameFreq == 0) && (frameTracker > 0)){
        vorResult.addFrame(img);
    }
}
  
    

 


