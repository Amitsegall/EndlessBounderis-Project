//
//  BackDiffClass.cpp
//  classCVtools
//
//  Created by Amit Segall on 23/03/2018.
//
//

#include "BackDiffClass.h"


void BackDiff::update(ofFbo mainOut,int threshold){
    //Getting a new frame
    
    ofPixels locPix;
    mainOut.readToPixels(locPix);
    
//    image.allocate(mainOut.getWidth(), mainOut.getHeight());
    image.setFromPixels(locPix);
    image.resize(640, 480);
    
    //Convert to grayscale image
    grayImage = image;
    
    //Smoothing image
    blurred = grayImage;
    blurred.blurGaussian( 9 );
    
    //Store first frame to background image
    if ( !background.bAllocated ) {
        background = blurred;
    }
    
    //Find difference of the frame and background
    diff = blurred;
    diff.absDiff(blurred, background); // get pixel difference
    
    //Thresholding for obtaining binary image
    mask = diff;
    mask.threshold( threshold) ; //set the  Threshold - very important
    //It should be adjusted for good results when using another videos than in example.
    
    //Find contours
    contourFinder.findContours(mask, 10, 20000, 20, false);
    
    //Store objects' centers
    blobs = contourFinder.blobs;
    
}

//________________________________________

void BackDiff::draw(){

//    mask.draw(0,0,ofGetWidth(),ofGetHeight());
    contourFinder.draw(0,0,ofGetWidth(),ofGetHeight()); // set visuals from the counterFinder
//    contourFinder.draw(0,0);
    
 
} // close draw



void BackDiff::setBack(){ // set new background to diff 
    background = blurred;
}



