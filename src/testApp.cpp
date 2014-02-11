#include "testApp.h"

#include <algorithm>

//--------------------------------------------------------------
void testApp::setup(){
    cam.initGrabber(1280, 720);
	tracker.setup();
    ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
    frequency = 440;
    vibrato = 0.5;

}

//--------------------------------------------------------------
void testApp::update(){
	cam.update();
	if(cam.isFrameNew()) {
		tracker.update(ofxCv::toCv(cam));
	}
    
    // Let's grab the 
    openMouth = tracker.getGesture(ofxFaceTracker::JAW_OPENNESS);
    eyebrow = tracker.getGesture(ofxFaceTracker::MOUTH_HEIGHT);
    
    // Sound attributes are a function of the person's face
    frequency = openMouth*17 + (openMouth*15 * 0.01);
    vibrato = eyebrow*15;
    
    
    vibrato = eyebrow;
    
}

//--------------------------------------------------------------
void testApp::draw(){
    // draw what the camera sees
    cam.draw(0, 0);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}


void testApp::audioRequested (float * output, int bufferSize, int nChannels){
    for (int i = 0; i < bufferSize; i++){
        // Since ofxTonic isn't cooperating, Andrew helped me populate the audio buffer
        // with *math*
        float rawDataShiftPos = n + sin(3.14 * 2 * n/44100.0)*0.3;
        
        output[i*nChannels] = (1.0-rawDataShiftPos) * sin(2 * 3.14 * n * frequency / 44100.0);
        output[i*nChannels + 1] = 0;
        n = (n+1) % (44100*4000);
	}
}