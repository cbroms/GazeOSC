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

	gui.add(host.set("Host", "10.0.0.170"));
	gui.add(port.set("Port", "8888"));

	gui.add(transformCoords.set("Transform Coordinates", false));
	gui.add(height.set("Height", "800"));
	gui.add(width.set("Width", "1200"));

	setupOsc();
}

void ofApp::setupOsc() {
	osc.setup(host, std::stoi(port));
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

		if (transformCoords) {
			map(leftData, ofGetScreenHeight(), std::stof(height), ofGetScreenWidth(), std::stof(width));
			map(rightData, ofGetScreenHeight(), std::stof(height), ofGetScreenWidth(), std::stof(width));
			
		}
		
		addMessage("/eye/left/x", leftData.x);
		addMessage("/eye/left/y", leftData.y);
		addMessage("/eye/right/x", rightData.x);
		addMessage("/eye/right/y", rightData.y);
	}

	if (sendGazePos) {

		ofPoint gazeData = eye.getGazePoint();

		if (transformCoords) {
			map(gazeData, ofGetScreenHeight(), std::stof(height), ofGetScreenWidth(), std::stof(width));
		}
		
		addMessage("/gaze/x", gazeData.x);
		addMessage("/gaze/y", gazeData.y);
	}

	if (sendFixationPos) {

		ofPoint fixationData = eye.getFixationPoint();

		if (transformCoords) {
			map(fixationData, ofGetScreenHeight(), std::stof(height), ofGetScreenWidth(), std::stof(width));
		}

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

void ofApp::map(ofPoint &point, float curHeight, float newHeight, float curWidth, float newWidth) {
	point.x = (point.x) / (curWidth) * (newWidth);
	point.y = (point.y) / (curHeight) * (newHeight);

//	cout << to_string(point.x) << " " << to_string(point.y) << endl;
}


//--------------------------------------------------------------
void ofApp::draw(){

	gui.draw();

	// draw osc settings info
	ofSetColor(0, 255, 0);
	string dest = "sending to " + osc.getHost() + ":" + std::to_string(osc.getPort());
	ofDrawBitmapString(dest, ofPoint(10, ofGetHeight() - 10));

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

	// on enter/return refresh the osc settings
	if (key == 13 || key == 'r') {
		setupOsc();
	}
}