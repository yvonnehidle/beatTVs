#pragma once

#include "ofMain.h"
#include "beatDetect.h"
#include "ofxOscilloscope.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);

    ofTrueTypeFont  fbook;
	void audioReceived(float* input, int bufferSize, int nChannels);

    beatDetect bd;
    ofSoundStream soundStream;
	ofxOscilloscope oscilloscope;
};

