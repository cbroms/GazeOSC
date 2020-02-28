#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	eye.setup();
	eye.registerEyePositionEventHandler();
	eye.registerGazePointEventHandler();
	eye.registerFixationEventHandler();

	gui.setup();
	gui.setName("GazeOSC");
	gui.setPosition(0, 0);
	gui.add(sendEyePos.set("Send Eye Position", true));
	gui.add(sendGazePos.set("Send Gaze Position", true));
	gui.add(sendFixationPos.set("Send Fixation Position", true));

	host = "127.0.0.1";
	port = 8833;

	osc.setup(host, port);
}

//--------------------------------------------------------------
void ofApp::update(){
	eye.update();
	sendGazeOsc();
}

//--------------------------------------------------------------
void ofApp::sendGazeOsc() {

	bundle.clear();

	if (sendEyePos) {

		ofPoint leftData = ofPoint(-1, -1);
		ofPoint rightData = ofPoint(-1, -1);

		if (eye.hasLeftEye()) {
			leftData = eye.getLeftEyeNormalized();
		}
		if (eye.hasRightEye()) {
			rightData = eye.getRightEyeNormalized();
		}
		
		addMessage("/eye/left/x", leftData.x);
		addMessage("/eye/left/y", leftData.y);
		addMessage("/eye/right/x", rightData.x);
		addMessage("/eye/right/y", rightData.y);
	}

	if (sendGazePos) {

		ofPoint gazeData = eye.getGazePoint();
		
		addMessage("/gaze/x", gazeData.x);
		addMessage("/gaze/y", gazeData.y);
	}

	if (sendFixationPos) {

		ofPoint fixationData = eye.getFixationPoint();

		addMessage("/fixation/x", fixationData.x);
		addMessage("/fixation/y", fixationData.y);
	}

	osc.sendBundle(bundle);
}

//--------------------------------------------------------------
void ofApp::addMessage(string address, float data) {
	ofxOscMessage msg;
	msg.setAddress(address);
	msg.addFloatArg(data);
	bundle.addMessage(msg);
}

//--------------------------------------------------------------
void ofApp::draw(){

	gui.draw();

	// Draw eye position
	ofSetColor(0, 255, 0);
	ofFill();
	if (eye.hasLeftEye())
	{
		ofPoint p = eye.getLeftEyeNormalized();
		ofDrawCircle(
			p.x * ofGetWidth(),
			p.y * ofGetHeight(),
			(1. - p.z) * 80);
	}
	if (eye.hasRightEye())
	{
		ofPoint p = eye.getRightEyeNormalized();
		ofDrawCircle(
			p.x * ofGetWidth(),
			p.y * ofGetHeight(),
			(1. - p.z) * 80);
	}

	// Draw gaze point
	ofSetColor(255, 255, 255);
	ofDrawCircle(eye.getGazePointData().X, eye.getGazePointData().Y, 20);
	
	// Draw fixation 
	ofSetColor(255, 0, 0);
	ofDrawCircle(eye.getFixationData().X, eye.getFixationData().Y, 10);
}

//--------------------------------------------------------------
void ofApp::exit() {
	
	eye.unregisterEyePositionEventHandler();
	eye.unregisterGazePointEventHandler();
	eye.unregisterFixationEventHandler();
	eye.close();
}

void ofApp::keyPressed(int key) {
	if (key == 'f') {
		ofToggleFullscreen();
	}
}