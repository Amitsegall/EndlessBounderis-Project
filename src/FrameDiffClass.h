//
//  FrameDiffClass.hpp
//  frameDiffClass
//
//  Created by Amit Segall on 10/04/2018.
//
//

#ifndef FrameDiffClass_hpp
#define FrameDiffClass_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxOpenCv.h"



class FrameDiff {
    
public:
    
    void update(ofFbo mainOut, float val1 , float val2);
    void draw(float val3);
    
  
    ofxCvColorImage image;		//The current video frame
    //The current and the previous video frames as grayscale images
    ofxCvGrayscaleImage grayImage, grayImagePrev;
    ofxCvGrayscaleImage diff;		//Absolute difference of the frames
    ofxCvFloatImage diffFloat;		//Amplified difference images
    ofxCvFloatImage bufferFloat;	//Buffer image
    
    bool debug;
    
    
private:
    
    
};


#endif /* FrameDiffClass_hpp */
