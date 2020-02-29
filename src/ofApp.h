#pragma once

#include "ofMain.h"
#include "ofxTobiiEyeX.h"
#include "ofxOsc.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();
		void keyPressed(int key);

		ofxTobiiEyeX eye;
		ofxOscSender osc;
		ofxOscBundle bundle;
		ofxPanel gui;

		ofParameter<bool> sendEyePos;
		ofParameter<bool> sendGazePos;
		ofParameter<bool> sendFixationPos;

		void addMessage(string address, float data);
		void setupOsc();
		void sendGazeOsc();

		void map(ofPoint &point, float curHeight, float newHeight, float curWidth, float newWidth);

		ofParameter<string> host;
		ofParameter<string> port;

		ofParameter<bool> transformCoords;
		ofParameter<string> height;
		ofParameter<string> width;
};
