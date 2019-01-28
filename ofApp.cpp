#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cam.initGrabber(ofGetWidth(), ofGetHeight());
    ofScale(-1, 1);
    
    contourFinder.setMinAreaRadius(100);
    contourFinder.setMaxAreaRadius(800);
    background.setLearningTime(900);
    background.setThresholdValue(20);
    
    
    //画面の基本設定
    //ofSetFrameRate(60);
    //ofBackground(0);
    
    
    //GUI
    resetBackgroundButton.addListener(this, &ofApp::resetBackgroundPressed);
    gui.setup();
    gui.add(bgThresh.setup("background thresh", 50, 0, 100));
    gui.add(contourThresh.setup("contour finder thresh", 127, 0, 255));
    gui.add(resetBackgroundButton.setup("reset background"));
    
    
    box2d.init();   //Box2dの世界の初期化
    box2d.setGravity(0,10); //重力を下向きに10
    //box2d.createBounds();   //地面を生成
    box2d.setFPS(30.0); //Box2Dの世界でのFPS
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    
    if (cam.isFrameNew()) {
        //背景差分画像を生成
        background.setThresholdValue(bgThresh);
        background.update(cam, thresholded);
        thresholded.update();
        
        //背景差分画像の輪郭抽出
        contourFinder.setThreshold(contourThresh);
        contourFinder.findContours(thresholded);
        
        edges.clear();
        shadowLines = contourFinder.getPolylines();
        for (unsigned int i = 0; i < shadowLines.size(); i++) {
            shadowLines[i].simplify();
            //新しいedgeを作る
            shared_ptr <ofxBox2dEdge> edge = shared_ptr<ofxBox2dEdge>(new ofxBox2dEdge);
            //lineからedgeを作る
            edge.get()->addVertexes(shadowLines[i]);
            //edgeをbox2dの世界に入れる
            edge.get()->create(box2d.getWorld());
            edges.push_back(edge);
        }
    }
    
    box2d.update(); //Box2Dの更新
}

//--------------------------------------------------------------
void ofApp::draw(){
    //ofScale(-1, 1);
    
    ofSetColor(255);
    cam.draw(0, 0);
    
    ofFill();
    ofSetLineWidth(1.0);
    //円を描画
    ofSetHexColor(0xf6c738);
    for (int i = 0; i < circles.size(); i++) {
        circles[i].get()->draw();
    }
    
    //四角を描画
    ofSetHexColor(0xBF2545);
    for(int i = 0; i < boxes.size(); i++) {
        boxes[i].get()->draw();
    }
    
    /*
    //edgeを描画
    ofSetLineWidth(3.0);
    ofSetColor(255, 0, 0);
    for (unsigned int i = 0; i < edges.size(); i++) {
        edges[i].get()->draw();
    }
    */
    
    //GUI
    gui.draw();
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'c') {
        float r = ofRandom(20, 50);
        //ofxBox2dCircleのインスタンスを新規作成し、そのptrをofPtrの形式で表し、ofPtrのベクトルであるcirclesに入れる
        circles.push_back(ofPtr<ofxBox2dCircle>(new ofxBox2dCircle));
        circles.back().get()->setPhysics(3.0, 0.53, 0.1);
        circles.back().get()->setup(box2d.getWorld(), mouseX, mouseY, r);
    }
    
    if (key == 'b') {
        float w = ofRandom(20, 50);
        float h = ofRandom(20, 50);
        boxes.push_back(ofPtr<ofxBox2dRect>(new ofxBox2dRect));
        boxes.back().get()->setPhysics(3.0, 0.53, 0.1);
        boxes.back().get()->setup(box2d.getWorld(), mouseX, mouseY, w, h);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}
//--------------------------------------------------------------
void ofApp::resetBackgroundPressed(){
    background.reset();
}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
