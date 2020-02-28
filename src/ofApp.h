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
		
		void sendGazeOsc();

		string host;
		int port;
		
};
