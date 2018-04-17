//
//  FrameDiffClass.cpp
//  frameDiffClass
//
//  Created by Amit Segall on 10/04/2018.
//
//

#include "FrameDiffClass.h"

void FrameDiff::update(ofFbo mainOut, float val1 , float val2){
   
        //Store the previous frame, if it exists till now
        if ( grayImage.bAllocated ) {
            grayImagePrev = grayImage;
        }
        
        //Getting a new frame
        ofPixels locPix;
        mainOut.readToPixels(locPix);
        image.setFromPixels(locPix);

        grayImage = image; //Convert to grayscale image
        
        //Do processing if grayImagePrev is inited
        if ( grayImagePrev.bAllocated ) {
            //Get absolute difference
            diff.absDiff( grayImage, grayImagePrev );
            
            //We want to amplify the difference to obtain
            //better visibility of motion
            //We do it by multiplication. But to do it, we
            //need to convert diff to float image first
            diffFloat = diff;	//Convert to float image
            diffFloat *= val1;	//Amplify the pixel values (original = 5.0)
            
            //Update the accumulation buffer
            if ( !bufferFloat.bAllocated ) {
                //If the buffer is not initialized, then
                //just set it equal to diffFloat
                bufferFloat = diffFloat;
            }
            else {
                //Slow damping the buffer to zero
                bufferFloat *= val2; //original = 0.85
                //Add current difference image to the buffer
                
                bufferFloat += diffFloat;
                bufferFloat.erode(); //helps get rid of noise (remove if not needed)
            }
        }
    
} // close update


void FrameDiff::draw(float val3){
  
    if ( diffFloat.bAllocated ) {
        //Get image dimensions
        int w = grayImage.width;
        int h = grayImage.height;
        
        //Set color for images drawing
        ofSetColor( 255, 255, 255 );
        
       // when working correctly this is how I draw to the screen
        //Get bufferFloat pixels
        float *pixels = bufferFloat.getPixelsAsFloats();
        
        //Scan all pixels
        for (int y=0; y<h; y+=1)
        {
            for (int x=0; x<w; x+=1)
            {
                //Get the pixel value
                float value = pixels[ x + w * y ];
                //If value exceed threshold, then draw pixel
                if ( value >= val3 ) {                           //original was 0.9
                   
                    int c1 = ofMap(x,0,w-1,0,255);
                    int c2 = ofMap(y,0,h-1,0,255);
                    ofSetColor(0,c1,c2);
                    ofRect( x, y, 1, 1 );
                    
                    
                    //                        } // if debug
                } // if pixel above tresh
            }
        }
    }
} // close draw
