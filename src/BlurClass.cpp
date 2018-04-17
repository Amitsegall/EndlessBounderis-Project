//
//  BlurClass.cpp
//  Term2AllTogether
//
//  Created by Amit Segall on 15/04/2018.
//
//

#include "BlurClass.h"

void BlurClass::setup() {
    
    // blur :
    ofFbo::Settings s;
    s.width = 1280;
    s.height = 800;
    s.internalformat = GL_RGBA;
    s.textureTarget = GL_TEXTURE_RECTANGLE_ARB;
    s.maxFilter = GL_LINEAR; GL_NEAREST;
    s.numSamples = 0;
    s.numColorbuffers = 1;
    s.useDepth = false;
    s.useStencil = false;
    
    gpuBlur.setup(s, false);
    gpuBlur.numBlurOverlays = 1;
    gpuBlur.blurOverlayGain = 255;
    gpuBlur.blurPasses = 5;
    
   
    
}

void BlurClass::update(float blurPasses){
    
     gpuBlur.blurOffset = blurPasses;
    
}

void BlurClass::blurBegin(){
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    gpuBlur.beginDrawScene();
    ofClear(0, 0, 0, 0);
}

void BlurClass::blurEnd(){
    //blur ends
    gpuBlur.endDrawScene();
    gpuBlur.performBlur();
    //overlay the blur on top
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); //pre-multiplied alpha
    gpuBlur.drawBlurFbo();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
}