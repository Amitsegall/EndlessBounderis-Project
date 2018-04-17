#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    int x = 640;
    int y = 480;
   //cam setup
    video.setGrabber(std::make_shared<ofxPS3EyeGrabber>());
    video.getGrabber<ofxPS3EyeGrabber>()->setAutoWhiteBalance(false);
    video.getGrabber<ofxPS3EyeGrabber>()->setLED(false);
    
    video.setDesiredFrameRate(30);
    
    video.setup(x, y);
    
    // new things to setup
    chess.load("chess640.jpg");
    debug = false; // switch cv to debug mode
    setCamParam = false;
    ofSetCircleResolution(100);
    mGrid.setup(x*2,y*2);
    ofSetBackgroundAuto(false);
    
    
    blur.setup(); // setup blur fx

    //init the FBO
    camImage.allocate(x, y,GL_RGBA);
    camImage.begin();
    ofClear(255, 255, 255,255);
    camImage.end();
    initImage.allocate(x, y,ofImageType::OF_IMAGE_COLOR_ALPHA);
    
    mainOut.allocate(1280, 800,GL_RGB); // otherwise the CV will fail - kill the alpah !
    mainOut.begin();
    ofClear(255, 255, 255);
    mainOut.end();
    
//    lSide.allocate(x, y,GL_RGBA);
//    lSide.begin();
//    ofClear(255, 255, 255,255);
//    lSide.end();
//    
//    rSide.allocate(x, y,GL_RGBA);
//    rSide.begin();
//    ofClear(255, 255, 255,255);
//    rSide.end();

    
    
    //flowtools
    flowTool.setup();
    ft2.setup();
    
    backDiff.setBack(); // create init background
    
    // checking if there is a homography matrix already
    ofFile previous("homography.yml");
    if(previous.exists()) {
        homo.setup("init.png","chess640.jpg");
        homoUp1 = true;
        homoUp2 = true;
    }else {
        homoUp1 = false;
        homoUp2 = false;
    }

    //Gui
    gui.setup();
    gui.add(brightness.set("brightness",0,0,255));
    gui.add(gain.set("gain",0,0,63));
    gui.add(contrast.set("constrast",35,0,255));
    gui.add(threshold.set("BD_threshold", 70, 0, 200));
    gui.add(buffFloat.set("FD_buffFloat", 8.85, 0, 10));
    gui.add(diffFloat.set("FD_diffFloat", 0.15, 0, 3));
    gui.add(valFloat.set("FD_valFloat", 2.8, 0, 3));
    gui.add(trail.set("trail", 200, 0, 255));
    gui.add(blurPasses.set("blur",3,0,10));
    
    menu = false; // show/hide gui
    

    
    
    
}// close setup

//--------------------------------------------------------------
void ofApp::update(){
    //gui update
    video.getGrabber<ofxPS3EyeGrabber>()->setBrightness(brightness);
    video.getGrabber<ofxPS3EyeGrabber>()->setGain(gain);
    video.getGrabber<ofxPS3EyeGrabber>()->setContrast(contrast);
	
    //frame update
    video.update();
    
    if (video.isFrameNew()){
        // creating an image from videos
        camImage.begin();
        video.draw(0, 0);
        camImage.end();

        homo.update(video);
        blur.update(blurPasses);
        
        //homography update
        
        if (homoUp1 && homoUp2){
            
            mainOut.begin();
            homo.draw();
            mainOut.end();

            backDiff.update(mainOut,threshold);
            frameDiff.update(mainOut,buffFloat,diffFloat);
            
            
            //test to do two desigens
//            ofPixels locPix;
//            ofImage lImg,rImg;
//    
//            mainOut.readToPixels(locPix);
//            lImg.setFromPixels(locPix);
//            rImg.setFromPixels(locPix);
//            
//            lSide.begin();
//            lImg.drawSubsection(0, 0, ofGetWidth()/2, ofGetHeight(), 0,0);
//            lSide.end();
//            
//            rSide.begin();
//            rImg.drawSubsection(ofGetWidth()/2, 0, ofGetWidth()/2, ofGetHeight(), ofGetWidth()/2,0);
//            rSide.end();
//    
            
            flowTool.update(mainOut);
            
//            ft2.update(rSide);
        }
    
    }// close new frame
    

} // close update

//--------------------------------------------------------------
void ofApp::draw(){

   
    if (homoUp1 && homoUp2){
        
        //_this is the MAGIC !!!!____
        
        //        mainOut.draw(0, 0); //test output of homography
       
        blur.blurBegin();

////        clear the back
//        ofPushStyle();
//        ofSetColor(255, trail);
//        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
//        ofPopStyle();

//        backDiff.draw();// draw blubs / centers / rects ?
      
//        frameDiff.draw(valFloat); // draw movements


//        mGrid.draw(mouseX, mouseY);
        
        blur.blurEnd();
        
        flowTool.drawFluidPressure();
//        lSide.draw(0, 0, ofGetWidth()/2, ofGetHeight());
//             flowTool.drawFluidPressure(0,0,ofGetWidth()/2,ofGetHeight());
//        ft2.drawFluidPressure();

        
    } else {
    chess.draw(0,0);
        
        if (homoUp1 && !homoUp2){
            homo.draw();
        }
    }
    
    if (setCamParam){
        video.draw(0, 0);
        if(debug){
        bnw(); // draw gray image
        }
        
    }
    if (menu){
     gui.draw();
     
        
    // check frame rates
    std::stringstream ss;
        
     ss << " App FPS: " << ofGetFrameRate() << std::endl;
     ss << " Cam FPS: " << video.getGrabber<ofxPS3EyeGrabber>()->getFPS()  << std::endl;
     ss << "Real FPS: " << video.getGrabber<ofxPS3EyeGrabber>()->getActualFPS();
        
     ofDrawBitmapStringHighlight(ss.str(), ofPoint(15, ofGetHeight()-50));
    }
    
}//close draw


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key) {
        case '1' : // set the chess board full screen on the output
            ofToggleFullscreen();
            chess.resize(ofGetWidth(), ofGetHeight());
            break;
        case '2' : // capture a new image from the camera
             initImg(camImage);
            break;
        case '3': // setup both images in the homography class
            homo.setup("chess640.jpg","init.png"); // setting up the chessboard and the image of the space(init)
            homoUp1 = true;
            break;
        case '4':
            homoUp2 = true;
//            backDiff.setBack();
            homo.saveHomo();
            ofClear(255);
            break;
        case '5':
            
            break;

        case 'p' :
           
            break;
            
        case 'c' :
            setCamParam = !setCamParam;
            break;
        case 'd' :
            debug = !debug;
            break;
            
        case 's' :
            backDiff.setBack(); // creat a new background
            break;
        case 'm' :
            menu = !menu;
            break;
        case 'f' :
            ofToggleFullscreen();
            break;
    }
    
}


//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    homo.mousePressed(x, y, button);
}
//--------------------------------------------------------------

void ofApp::mouseDragged(int x, int y, int button){
    homo.mouseDragged(x, y, button);
}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    homo.mouseReleased(x, y, button);
}
//--------------------------------------------------------------
void ofApp::initImg(ofFbo input){
    ofPixels locPix;
    input.readToPixels(locPix);
    initImage.setFromPixels(locPix);
    ofSaveImage(initImage,"init.png");
}
//--------------------------------------------------------------

void ofApp::bnw(){
    ofxCvColorImage image;
    ofxCvGrayscaleImage gray;
    image.allocate(640, 480);
    gray.allocate(640, 480);
    image.setFromPixels(video.getPixelsRef());
    gray = image;
    gray.draw(0,0);
}



