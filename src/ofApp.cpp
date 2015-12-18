#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	this->settings = new ofxXmlSettings();
	this->settings->loadFile("config.xml");

	//Float FrameRate
	this->dataToScreenLeft.precision(3);
	this->dataToScreenRight.precision(3);

	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofDisableArbTex();
	
	/*ofEnableAntiAliasing();
	ofEnableSmoothing();*/

	this->matrixMapTextur = new MatrixMap(this->settings->getValue("settings:mapLoadTextur", 0) == 1);
	this->listBus = new ParsingBus(this->settings->getValue("settings:urlBus", URLPORTLAND), this->settings->getValue("settings:maxBus", 0));
	this->cam = new CamControl();

	ofSetBackgroundColor(ofColor::fromHex(0x8b8c8d));
	ofSetFullscreen(this->settings->getValue("settings:fullScreen", 0)==1);


}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	//Set random Speed Camera (1000 frames)
	if (frNumRand < ofGetFrameNum()) {
		randCam = (rand() % (3 + 1 - -3)) + -3;
		this->cam->setParamCam(this->cam->getDistanceToObj(), (float(0.1) * randCam), this->cam->getHeightCamera());
		frNumRand = ofGetFrameNum() + RANDANIMROTATCAM;
	}

	//Background Gradient
	glBegin(GL_QUAD_STRIP);
	glColor3f(0.0745, 0.384, 0.635);
	glVertex3f(0, 0, 0);
	glVertex3f(ofGetWidth(), 0, 0);

	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(0, ofGetHeight() / 2, 0);
	glVertex3f(ofGetWidth(), ofGetHeight() / 2, 0);

	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0, ofGetHeight(), 0);
	glVertex3f(ofGetWidth(), ofGetHeight(), 0);
	glEnd();
	
	this->cam->camBegin();
	
	//ofFill();
	//ofSetSmoothLighting(true);

	//Grid
	if (keyMode[1]) {
		ofDrawGrid(100.0, 1000, false, false, false, true);
	}
	//ofDrawGrid(50.0, 1000, false, false, true, false);
	//ofDrawGrid(50.0, 1000, false, true, false, false);

	//Map with texture
	if (keyMode[0]) {
		matrixMapTextur->draw();
	}

	//Bus
	this->listBus->draw(keyMode[2], keyMode[3]);

	//If i send a ofVec3f * => fail...
	this->cam->update(*this->listBus->getPositionBus());
	this->cam->camEnd();

	//Data label 2d
	ofSetColor(0, 0, 0, 255.0);
	this->dataToScreenLeft.str("");
	this->dataToScreenLeft << this->listBus->getDataBus() << std::endl;
	ofDrawBitmapString(this->dataToScreenLeft.str(), 5, 14);

	this->dataToScreenRight.str("");
	this->dataToScreenRight << "FPS : " << ofGetFrameRate() << std::endl;
	ofDrawBitmapString(this->dataToScreenRight.str(), ofGetWidth()-85, 14);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	//Get param camera
	float addRot = this->cam->getSpeedRotation();
	float addHeightCam = this->cam->getHeightCamera();
	float dist = this->cam->getDistanceToObj();

	switch (key)
	{
	case OF_KEY_F1: keyMode[0] = !keyMode[0];
		break;
	case OF_KEY_F2: keyMode[1] = !keyMode[1];
		break;
	case OF_KEY_F3: keyMode[2] = !keyMode[2];
		break;
	case OF_KEY_F4: keyMode[3] = !keyMode[3];
		break;
	case OF_KEY_RIGHT: addRot += float(0.1);
		break;
	case OF_KEY_LEFT: addRot -= float(0.1);
		break;
	case OF_KEY_DOWN: addHeightCam += float(0.025);
		break;
	case OF_KEY_UP: addHeightCam -= float(0.025);
		break;
	case OF_KEY_F11: {
		fullScreen = !fullScreen;
		ofSetFullscreen(fullScreen);
		break; }

	case OF_KEY_PAGE_DOWN:
		dist -= 25.0;
		break;

	case OF_KEY_PAGE_UP:
		dist += 25.0;
		break;

	default:
		break;
	}
	this->cam->setParamCam(dist, addRot, addHeightCam);
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
