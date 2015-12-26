#pragma once

#include "ofMain.h" 
#include "ofxXmlSettings\src\ofxXmlSettings.h"

#include "MatrixMap.h"
#include "ParsingBus.h"
#include "CamControl.h"

#define RANDANIMROTATCAM 1000
/**********************************************************************************************//**
 * \class	ofApp
 *
 * \brief	An of application.
 *
 * \author	Nicolas
 * \date	10/12/2015
 **************************************************************************************************/
class ofApp : public ofBaseApp{

	public:
		/**********************************************************************************************//**
		 * \fn	void ofApp::setup();
		 *
		 * \brief	Setups this object.
		 **************************************************************************************************/
		void setup();

		/**********************************************************************************************//**
		 * \fn	void ofApp::update();
		 *
		 * \brief	Updates this object.
		 **************************************************************************************************/
		void update();

		/**********************************************************************************************//**
		 * \fn	void ofApp::draw();
		 *
		 * \brief	Draws this object.
		 **************************************************************************************************/
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

	private:
		
		bool fullScreen = false;
		bool autoCam = true;
		bool keyMode[7] = {true, true ,true ,true ,false, true, true };
		bool keyIsDown[255];
		float speedCam = 5.0;

		stringstream dataToScreenLeft;
		stringstream dataToScreenLeftHelp;
		stringstream dataToScreenRight;
		
		uint64_t frNumRand = 0;
		int randCam = 1;
		int randCamNext = -1;

		ofxXmlSettings * settings;
		CamControl * cam;
		MatrixMap * matrixMapTextur;
		ParsingBus * listBus;

};
