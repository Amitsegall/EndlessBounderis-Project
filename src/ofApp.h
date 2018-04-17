#pragma once
#include "ofMain.h"

// addons
#include "ofxGui.h"
#include "ofxPS3EyeGrabber.h"

// my classes
#include "BackDiffClass.h"
#include "FrameDiffClass.h"
#include "homoClass.h"
#include "blurClass.h" // based on FboBlur addon
#include "MagneticGrid.h"
#include "FlowToolsClass.h"


class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
    void mousePressed(int x, int y, int button);
    void mouseDragged(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void keyPressed(int button);
    
    
    
	ofVideoGrabber video;
    

    bool debug;

    //gui
    ofxPanel gui;
    
    ofParameterGroup guiGrup;
    ofParameter<int> gain;
    ofParameter<int> brightness;
    ofParameter<int> contrast;
    ofParameter<int> threshold;
    ofParameter<float> buffFloat;
    ofParameter<float> diffFloat;
    ofParameter<float> valFloat;
    ofParameter<int> trail;
    ofParameter<float> blurPasses;

    bool menu; // show gui

    
    BlurClass blur;
    
    //CV classes 
    BackDiff backDiff;
    FrameDiff frameDiff;
    FlowToolsClass flowTool;
    FlowToolsClass ft2;
    
    
    // homography class
    HomoClass homo;
    bool homoUp1,homoUp2;
    
    // General things:
    ofImage chess,initImage,camImg;
    ofFbo camImage;
    ofFbo mainOut;
    ofFbo lSide,rSide;
    
    
    MagneticGrid mGrid;
  
    ofPixels currentPixels,outPixels;
    void initImg(ofFbo input);
    void bnw();
    bool setCamParam;
    
   
    
    
   
    
};

