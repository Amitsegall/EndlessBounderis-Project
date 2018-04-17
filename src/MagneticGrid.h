//
//  MagneticGrid.hpp
//  Term2AllTogether
//
//  Created by Amit Segall on 15/04/2018.
//
//

#ifndef MagneticGrid_hpp
#define MagneticGrid_hpp

#include <stdio.h>
#include "ofMain.h"

class MagneticGrid {
    
public:
    
    
    void setup(int x, int y);
    void draw(int mouseX,int mouseY);
    
    
    
    
    // variables
    
    int numOfXTiles,numOfYTiles,spaceX,spaceY,startX,startY;
    
    
    
    
private:
};



#endif /* MagneticGrid_hpp */
