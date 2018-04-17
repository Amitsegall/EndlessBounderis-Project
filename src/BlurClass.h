//
//  BlurClass.hpp
//  Term2AllTogether
//
//  Created by Amit Segall on 15/04/2018.
//
//

#ifndef BlurClass_hpp
#define BlurClass_hpp

#include <stdio.h>
#include "ofxFboBlur.h" // blur addon
#include "ofMain.h"



class BlurClass {
    
public:
    
    
    void setup();
    void update(float blurPasses);
    void blurBegin();
    void blurEnd();
    
    
    
    
    // variables
    
    // blur fx :
    ofxFboBlur gpuBlur;
    
    
    
    
private:
}; 


#endif /* BlurClass_hpp */
