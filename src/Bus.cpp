#include "Bus.h"

Bus::Bus()
{
	this->mutLock = new mutex();
	this->idBus = -1;
	for (int i = 0; i < sizeMaxHistory; i++) {
		this->historyPos[i] = nullptr;
	}

	this->sphereBus = new ofSpherePrimitive();
	this->sphereBus->setPosition(0.0, 0.0, 20);
	this->sphereBus->setRadius(radiusB);

	this->lineBus = new ofPolyline();
	this->lineBus->addVertex(0.0, 0.0, 0.0);
	this->lineBus->addVertex(0.0, 0.0, 20);

	for (int i = 0; i < 8; i++) {
		this->effecBlur[i] = new ofSpherePrimitive();
		this->effecBlur[i]->setPosition(0.0, 0.0, 20);
		this->effecBlur[i]->setRadius((i/1.5)+ radiusB);
	}
}

int Bus::getId() {
	return this->idBus;
}
ofVec3f * Bus::getPosBus() {
	return &this->sphereBus->getPosition();
}

ofSpherePrimitive* Bus::getBus() {
	return this->sphereBus;
}

string Bus::getData() {
	return this->fullDataBus;
}

void Bus::setId(int id) {
	this->idBus = id;
}

void Bus::setData(string dat) {
	this->dataBus = dat;
}

void Bus::setFullData(string fDat) {
	this->fullDataBus = fDat;
}

void Bus::setBlur(bool b) {
	this->blur = b;
}

void Bus::setRadius(float i) {
	radiusB = i;
	this->sphereBus->setRadius(radiusB);
	for (int r = 0; r < 8; r++) {
		this->effecBlur[r]->setRadius((r / 1.5) + radiusB);
	}
}

bool Bus::getExist() {
	return this->exist;
}

void Bus::setExist(bool e) {
	this->exist = e;
}

void Bus::setCoord(float x, float y) {
	
	posXYZBus *newPos = new posXYZBus();
	newPos->x = x;
	newPos->y = y;

	this->mutLock->lock();
	//Decal History
	for (int i = sizeMaxHistory - 1; i > -1; i--) {
		this->historyPos[i] = this->historyPos[i - 1];
	}
	//Delete last pos
	if (this->historyPos[sizeMaxHistory - 1] != nullptr)
	{
		delete this->historyPos[sizeMaxHistory - 1];
	}

	//Calcul Z
	if (this->historyPos[1] != NULL) {
		if (newPos->x == this->historyPos[1]->x && newPos->y == this->historyPos[1]->y) {
			if (this->noMove < 12) {
				this->noMove += 1;
			}
		}
		else {
			this->noMove = 1;
		}
	}
	newPos->z = (20.0 * this->noMove);

	//Add new Poss
	this->historyPos[0] = newPos;
	this->animBus = 1.0;

	if (sizeHistPos < (sizeMaxHistory - 1)) {
		sizeHistPos += 1;
	}
	this->mutLock->unlock();
}

void Bus::update() {
	
}

void Bus::draw(bool drag, bool showDat) {

	float newX = 0.0;
	float newY = 0.0;
	float newZ = 20;
	this->mutLock->lock();
	if (this->historyPos[1] != nullptr) {
		
		newX = (((this->historyPos[0]->x - this->historyPos[1]->x)*this->animBus) - this->historyPos[0]->x);
		newY = (((this->historyPos[0]->y - this->historyPos[1]->y)*this->animBus) - this->historyPos[0]->y);
		newZ = -(((this->historyPos[0]->z - this->historyPos[1]->z)*this->animBus) - this->historyPos[0]->z);
		this->sphereBus->setPosition(newX, newY, newZ);
		
		this->lineBus->clear();
				
		//glColor4f(0.21875, 0.57421875, 0.83203125, 0.7);
		// Draw the blue wall 
		if (drag) {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(0.21875, 0.57421875, 0.83203125, 0.3);

			glBegin(GL_QUAD_STRIP);
			for (int s = (sizeHistPos - 1); s > 1; s--) {
				glVertex3f(-this->historyPos[s]->x, -this->historyPos[s]->y, 0.0);// WARNING - if inverse
				glVertex3f(-this->historyPos[s]->x, -this->historyPos[s]->y, this->historyPos[s]->z);

				//this->lineBus->addVertex(this->history->get(s)->x, this->history->get(s)->y, this->history->get(s)->z);
			}
			glVertex3f(newX, newY, 0.0);
			glVertex3f(newX, newY, newZ);
			glEnd();
		}
	
		
		this->lineBus->addVertex(newX, newY, 0.0);
		this->lineBus->addVertex(newX, newY, newZ);

		for (int i = 0; i < 8; i++) {
			this->effecBlur[i]->setPosition(newX, newY, newZ);
		}
		
		if (this->animBus > 0) {
			this->animBus -= 0.0025;//Var anim
		}
	}

	ofSetColor(0, 0, 0);
	this->lineBus->draw();

	if (this->blur) {
		float alph = 10.0;
		for (int i = 7; i > 0; i--) {
			ofSetColor(ofColor::fromHex(0x38aed5, alph));
			this->effecBlur[i]->draw();
			alph += 15.0;
		}
	}

	ofSetColor(ofColor::fromHex(0xe1f8ff));
	this->sphereBus->draw();
	ofSetColor(ofColor::fromHex(0x000000));

	if (showDat && this->historyPos[1] != nullptr) {
		ofDrawBitmapString(dataBus, newX + 5, newY, newZ + 5);
	}
	this->mutLock->unlock();
}


Bus::~Bus()
{
	this->mutLock->lock();
	for (int i = sizeMaxHistory - 1; i > -1; i--) {
		delete this->historyPos[i];
	}
	for (int i = 0; i < 8; i++) {
		delete this->effecBlur[i];
	}

	delete this->sphereBus;
	this->lineBus->clear();
	delete this->lineBus;

	this->mutLock->unlock();
	delete this->mutLock;
	//Not Working...
	//delete[] this->historyPos;
	//delete[] this->effecBlur;
	ofLogNotice("ofApp::setup") << "Bus removed";
}
