#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"
#include "ofxBox2d.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void resetBackgroundPressed();
    
    static const unsigned int MAX_BLOBS = 4;
		
    ofVideoGrabber cam;
    
    std::vector<ofPolyline> shadowLines;
    ofxBox2d box2d;         //Box2Dの世界
    vector <ofPtr<ofxBox2dCircle>> circles;  //円
    vector <ofPtr<ofxBox2dRect>> boxes; //四角
    vector <shared_ptr<ofxBox2dEdge>> edges;    //edges
    vector <ofPolyline> lines;  //drawed lines
    
    ofxCv::ContourFinder contourFinder;
    ofxCv::RunningBackground background;
    ofImage thresholded;
    
    ofxPanel gui;
    ofxFloatSlider bgThresh;    //背景差分の閾値
    ofxFloatSlider contourThresh;   //輪郭抽出の閾値
    ofxButton resetBackgroundButton;    //背景リセットボタン
};
