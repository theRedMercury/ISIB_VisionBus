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
	
	//Conf aliasing/smoothing
	if (this->settings->getValue("settings:antiAliasing", 0) == 1) {
		ofEnableAntiAliasing();
	}
	if (this->settings->getValue("settings:smoothing", 0) == 1) {
		ofEnableSmoothing();
	}
	
	this->randCamNext = this->settings->getValue("settings:randCamRot", RANDANIMROTATCAM);
	
	//Creat main objects
	this->matrixMapTextur = new MatrixMap(this->settings->getValue("settings:mapLoadTextur", 0) == 1);
	this->listBus = new ParsingBus(this->settings->getValue("settings:urlBus", URLPORTLAND), 
									this->settings->getValue("settings:maxBus", 0));
	
	this->cam = new CamControl();
	this->autoCam = this->settings->getValue("settings:camControl", 0) == 1;

	ofSetBackgroundColor(ofColor::fromHex(0x8b8c8d));
	ofSetFullscreen(this->settings->getValue("settings:fullScreen", 0)==1);
	ofSetWindowTitle("ISIB Vision Bus 1.0");

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
		frNumRand = ofGetFrameNum() + this->randCamNext;
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

	//ControlCam
	if (keyIsDown[122]) {
		this->cam->backForwardCam(-this->speedCam);}
	if (keyIsDown[115]) {
		this->cam->backForwardCam(this->speedCam);
	}
	if (keyIsDown[113]) {
		this->cam->leftRightCam(-this->speedCam);
	}
	if (keyIsDown[100]) {
		this->cam->leftRightCam(this->speedCam);
	}
	if (keyIsDown[97]) {
		this->cam->rotatCam(1.0);
	}
	if (keyIsDown[101]) {
		this->cam->rotatCam(-1.0);
	}
	if (keyIsDown[114]) {//+ R
		this->speedCam += 0.2;
	}
	if (keyIsDown[102]) {//- F
		this->speedCam -= 0.2;
	}

	this->cam->camBegin();

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

	if (this->autoCam) {
		//If i send a ofVec3f * => fail...
		this->cam->update(*this->listBus->getPositionBus());
	}

	this->cam->camEnd();

	//Show Help
	if (keyMode[4]) {
		ofSetColor(0, 175, 0, 255.0);
		this->dataToScreenLeftHelp.str("");
		this->dataToScreenLeftHelp << "\nF1 : Help :\n  1 : Show Map\n  2 : Show Grid\n  3 : Course" ;
		this->dataToScreenLeftHelp << "\n  4 : Data Bus\n  5 : Lock Bus\n  6 : Next Bus";
		this->dataToScreenLeftHelp << "\n  7 : Free Cam\n F2 : Show Data\n F3 : Show FPS\nF11 : FullScreen" << std::endl;
		ofDrawBitmapString(this->dataToScreenLeftHelp.str(), 5, 55);
	}

	//Data label 2d
	if (keyMode[5]) {
		ofSetColor(0, 0, 0, 255.0);
		this->dataToScreenLeft.str("");
		this->dataToScreenLeft << this->listBus->getDataBus() << std::endl;
		ofDrawBitmapString(this->dataToScreenLeft.str(), 5, 14);
	}

	//Show FPS
	if (keyMode[6]) {
		ofSetColor(0, 0, 0, 255.0);
		this->dataToScreenRight.str("");
		this->dataToScreenRight << "FPS : " << ofGetFrameRate() << std::endl;
		ofDrawBitmapString(this->dataToScreenRight.str(), ofGetWidth() - 85, 14);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	keyIsDown[key] = true;
	//ofLogNotice("ofApp::setup") << key;
	/*float speedM = 5.0;
	switch (key)
	{
	case 122: this->cam->backForwardCam(-speedM);
		break;
	case 115: this->cam->backForwardCam(speedM);
		break;
	case 113: this->cam->leftRightCam(-speedM);
		break;
	case 100: this->cam->leftRightCam(speedM);
		break;
	case 97: this->cam->rotatCam(-speedM);
		break;
	case 101: this->cam->rotatCam(speedM);
		break;
	}*/
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	keyIsDown[key] = false;
	//Get param camera
	float addRot = this->cam->getSpeedRotation();
	float addHeightCam = this->cam->getHeightCamera();
	float dist = this->cam->getDistanceToObj();
	//ofLogNotice("ofApp::setup") << key;
	/*	38	=	1
		233	=	2
		34	=	3
		39	=	4
		40	=	5
		167 =	6
		232 =	7
		122 =	Z
		115	=	S
		113 =	Q	
		100	=	D
	*/
	switch (key)
	{
	case OF_KEY_F1: keyMode[4] = !keyMode[4];
		break;
	case OF_KEY_F2: keyMode[5] = !keyMode[5];
		break;
	case OF_KEY_F3: keyMode[6] = !keyMode[6];
		break;
	case 38: keyMode[0] = !keyMode[0];
		break;
	case 233: keyMode[1] = !keyMode[1];
		break;
	case 34: keyMode[2] = !keyMode[2];
		break;
	case 39: keyMode[3] = !keyMode[3];
		break;
	case 232: this->autoCam = !this->autoCam;
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
