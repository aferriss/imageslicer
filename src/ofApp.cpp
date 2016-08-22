#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    file = "images/snowdenBW-small.jpg";
    img.load(file);
    
    w = img.getWidth();
    h = img.getHeight();
    
    ofSetWindowShape(w, h);
    
    fbo.allocate(w, h);
    
    genXYPositions();
    
    save = false;
    doWidth = true;
    copyToImg = false;
    justRendered = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    if(save){
        ofPixels savePix;
        fbo.readToPixels(savePix);
        ofSaveImage(savePix, "saved/"+ofGetTimestampString()+".png");
        save = false;
    }
    
    if(copyToImg){
        ofPixels imgPix;
        fbo.readToPixels(imgPix);
        img.setFromPixels(imgPix);
        justRendered = true;
        copyToImg = false;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.begin();
    
    img.draw(0,0);
    if(!justRendered){
        if(doWidth){
            for(int i = 0; i<xPositions.size()-1; i++){
                int xWidth = xPositions[i+1] - xPositions[i];
                img.drawSubsection(xPositions[i], yPositions[i], xWidth, h, xPositions[i], 0 );
            }
        }
        else if(!doWidth){
            for(int i = 0; i<yPositions.size()-1; i++){
                int yHeight = yPositions[i+1] - yPositions[i];
                img.drawSubsection(xPositions[i], yPositions[i], w, yHeight, 0, yPositions[i] );
            }
        }
    }
    fbo.end();
    
    fbo.draw(0,0);
    
//    cout<<ofToString(ofSignedNoise(ofGetFrameNum()*0.001))<<endl;
}
//--------------------------------------------------------------
void ofApp::genXYPositions(){
    int sumY = 0;
    int sumX = 0;
    int extraMin = 40;
    int extraMax = 100;
    int extraThresh = 9;
    
    int barMin = 2;
    int barMax = 4;
    
    int offSet = 10;
    yPositions.clear();
    xPositions.clear();
    justRendered = false;
    
    if(doWidth){
        for(int i = 0; i<w; i++){
            int r = ofRandom(10);
            int extra = 0;
            if(r>extraThresh){
                extra = ofRandom(extraMin,extraMax)*(int)ofRandom(-2, 2);
            }
            int randX = (int)ofRandom(barMin,barMax)+extra;
            int randY = (int)ofRandom(-offSet,offSet);
            sumX += randX;
            
            if( sumX  < w ){
                xPositions.push_back(sumX);
                yPositions.push_back(randY+extra);
            }
        }
    } else if (!doWidth){
        for(int i = 0; i<h; i++){
            int r = ofRandom(10);
            int extra = 0;
            if(r>extraThresh){
                extra = ofRandom(extraMin,extraMax)*(int)ofRandom(-2, 2);
            }
            int randY = (int)ofRandom(barMin,barMax)+extra;
            int randX = (int)ofRandom(-offSet,offSet);
            sumY += randY;
            
            if( sumY  < h){
                yPositions.push_back(sumY);
                xPositions.push_back(randX+extra);
            }
        }
    }
    
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'g'){
        genXYPositions();
    }
    if(key == 's'){
        save = true;
    }
    if(key == 'x'){
        doWidth = !doWidth;
        genXYPositions();
    }
    if(key == 'r'){
        copyToImg = true;
    }
    
    if(key == 'q'){
        img.load(file);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
