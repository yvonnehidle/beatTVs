#include "testApp.h"
#include "beatDetect.h"

int testApp_buffer_size = 1024;

bool detect=true;
bool drumVisible = true;
bool snareVisible = true;
bool hihatVisible = true;
ofImage bgImg;
float oscilloscopeBuffer[1024];
float phase = 0;

//--------------------------------------------------------------
void testApp::setup(){
    ofSetWindowTitle("beatTVs");
    bgImg.loadImage("stackedtvs.png");
	ofSetFrameRate(60);

	fbook.loadFont("robothead.ttf", 30, true, false);

	ofSoundStreamSetup(0, 1, this, 44100, testApp_buffer_size, 4);
	soundStream.setup(this, 0, 1, 44100, 1024, 1);

    oscilloscope.setup(44100);
	ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void testApp::audioReceived(float* input, int bufferSize, int nChannels) {
    bd.audioReceived(input, bufferSize);

    for(int i = 0; i < bufferSize; i++)
    {
        oscilloscopeBuffer[i] = input[i];
	}
	oscilloscope.analyze(oscilloscopeBuffer, bufferSize);
}

//--------------------------------------------------------------
void testApp::update() {
    bd.updateFFT();
}

//--------------------------------------------------------------
void testApp::draw()
{
    bgImg.draw(0,0);
    char str[32];


    //oscilloscope 1
    ofPushMatrix();
    ofRotateY(-10);
    oscilloscope.draw(295, 540, 200, 150);
    ofPopMatrix();


    // blue bars
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(303,95);
    ofRotateY(-18);
    ofSetColor(155,155,75);
    for (int i = 1; i < (int)148/2; i++)
    {
        if(i % 16 == 0)
        {
            ofSetColor(200,0,0);
        }
        else
        {
            ofSetColor(68,169,254);
            ofLine(10+(i*3),150,  10+(i*3),150-bd.magnitude[i]*5.0f);
        }
	}
	ofPopMatrix();


    // red bars
    ofPushMatrix();
    ofTranslate(623,90);
    ofRotateY(-28);
    for (int i = (int)130/2,b = 1; i<130 ; i++)
    {
        if(i % 16 == 0)
        {
            ofSetColor(200,0,0);
        }
        else
        {
            ofSetColor(246,0,64);
            ofLine(10+(b*3),200,  10+(b*3),200-bd.magnitude[i]*15.0f);
            b++;
        }
	}
	ofPopMatrix();


    // green bars
    ofPushMatrix();
    ofTranslate(120,200);
    ofRotateY(-48.5);
    ofSetColor(134,113,89);
	for (int i = 1; i < (int)238/2; i++)
	{
        if(i % 16 == 0)
        {
            ofSetColor(200,0,0);
        }
        else
        {
            ofSetColor(77,238,60);
            ofLine(10+(i*3),300,  10+(i*3),300-bd.magnitude_average[i]*7.0f);
        }
	}
	ofPopMatrix();


	// white bars
    ofPushMatrix();
    ofTranslate(565,370);
    ofRotateY(40);
    for (int i = (int)275/2,b = 1; i<275 ; i++)
    {
        if(i % 16 == 0)
        {
            ofSetColor(200,0,0);
        }
        else
        {
            ofSetColor(255,255,255);
            ofLine(10+(b*3),150,  5+(b*3),180-bd.magnitude[i]*15.0f);
            b++;
        }
	}
	ofPopMatrix();


    // yellow bars
    ofPushMatrix();
    ofTranslate(112,235);
    ofRotateY(41);
    for (int i = (int)73/2,b = 1; i<73 ; i++)
    {
        if(i % 16 == 0)
        {
            ofSetColor(200,0,0);
        }
        else
        {
            ofSetColor(226,238,32);
            ofLine(10+(b*3),0,  10+(b*3),0-bd.magnitude_average[i]*8.0f);
            b++;
        }
	}
	ofPopMatrix();
	ofPopStyle();


    // drum
    ofPushMatrix();
    ofRotateY(28);
    if(drumVisible){
        if(bd.isBeatRange(0,2,2))
        {
            ofPushStyle();
            ofSetColor(255,0,0);
            fbook.drawString("PercussionA",450,380);
            ofPopStyle();
        }
        else
        {
            ofPushStyle();
            ofSetColor(255,255,255);
            fbook.drawString("PercussionA",450,380);
            ofPopStyle();
        }
    }


    // snare
    if(snareVisible){
        if(bd.isBeatRange(12,18,4))
        {
            ofPushStyle();
            ofSetColor(255,0,0);
            fbook.drawString("PercussionB", 480, 430);
            ofPopStyle();
        }
        else
        {
            ofPushStyle();
            ofSetColor(255,255,255);
            fbook.drawString("PercussionB", 480, 430);
            ofPopStyle();
        }
    }

    // hihat
    if(hihatVisible){
        if(bd.isBeatRange(27,31,3))
        {
            ofPushStyle();
            ofSetColor(255,0,0);
            fbook.drawString("PercussionC", 430, 470);
            ofPopStyle();
        }
        else
        {
            ofPushStyle();
            ofSetColor(255,255,255);
            fbook.drawString("PercussionC", 430, 470);
            ofPopStyle();
        }
    }
    ofPopMatrix();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

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
