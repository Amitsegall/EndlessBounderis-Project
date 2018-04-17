//
//  MagneticGrid.cpp
//  Term2AllTogether
//
//  Created by Amit Segall on 15/04/2018.
//
//

#include "MagneticGrid.h"

void MagneticGrid::setup(int x, int y){
    numOfXTiles = 20;
    numOfYTiles = 20;
    spaceX= x / numOfXTiles;
    spaceY= y / numOfYTiles ;
    startX = spaceX/2;
    startY = spaceY/2;
    
}

void MagneticGrid::draw(int mouseX , int mouseY){
    for (int x = 0; x < numOfXTiles; x++){
        for (int y = 0; y < numOfYTiles;y++){
           
            int locX = startX + x * spaceX;
            int locY = startY + y * spaceY;
            
            ofPushStyle();
            ofPushMatrix();
            ofSetRectMode(OF_RECTMODE_CENTER);
            ofSetColor(0);
            ofTranslate(locX,locY);
            //float angle = atan2(mouseY-locY, mouseX-locX);
            ofRotate(180+ofRadToDeg(atan2(mouseY-locY, mouseX-locX)));
            
            ofDrawRectangle(0,0,50,5);
            ofPopMatrix();
            ofPopStyle();
        }
    }
} // close Draw