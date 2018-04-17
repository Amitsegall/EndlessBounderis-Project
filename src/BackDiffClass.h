//
//  BackDiffClass.hpp
//  classCVtools
//
//  Created by Amit Segall on 23/03/2018.
//
//

#ifndef BackDiffClass_hpp
#define BackDiffClass_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxOpenCv.h"


class BackDiff {
  
public:
    
    void update(ofFbo mainOut,int threshold);
    void draw();
    void setBack();
    
    ofxCvColorImage image;
    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage blurred;
    ofxCvGrayscaleImage background;
    ofxCvGrayscaleImage diff;
    ofxCvGrayscaleImage mask;
    
    ofxCvContourFinder 	contourFinder;
    
    vector<ofxCvBlob>  blobs;
    
    void mousePressed(int x, int y, int button);
    void keyPressed(int button);
    
    

    
};




#endif /* BackDiffClass_hpp */
