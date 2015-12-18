#include "CamControl.h"


CamControl::CamControl()
{
	this->camera = new ofEasyCam();
}

void CamControl::camBegin()
{
	this->camera->begin();
}
void CamControl::camEnd()
{
	this->camera->end();
}

float CamControl::getSpeedRotation()
{
	return this->speedRotation;
}
float CamControl::getHeightCamera()
{
	return this->heightCamera;
}
float CamControl::getDistanceToObj()
{
	return this->distanceToObj;
}

void CamControl::update(ofVec3f & data)
{
	float bx = data.x;
	float by = data.y;
	float bz = data.z*this->heightCamera;

	//Spherique Coord Calcul
	float teta = 45.0;
	float eyeX = bx + this->distanceToObj*cos(rot* (PI / 180.0))*sin(teta* (PI / 180.0));
	float eyeY = by + this->distanceToObj*sin(rot* (PI / 180.0))*sin(teta* (PI / 180.0));
	float eyeZ = this->distanceToObj*cos(teta* (PI / 180.0));

	//Does not work like I want :
	//cam.lookAt( ofVec3f(listBus->getPositionBus()->x, listBus->getPositionBus()->y, 0.0));

	float eyeZZ = (eyeZ - (bz * 3));
	if (eyeZZ < float(1.0)) {
		eyeZZ = float(1.0);
	}
	this->camera->setGlobalPosition(ofVec3f(eyeX, eyeY, eyeZZ)); //CodeOK
	this->camera->setTarget(ofVec3f(bx, by, bz));

	if (bz > float(105.0)) {
		bz = float(105.0);
	}
	this->camera->setOrientation(ofVec3f(35.0 + (bz*0.8), 0.0, rot + 90.0));

	//Anime Rotation
	rot += this->speedRotation;
	if (rot >= 360) {
		rot = 0.0;
	}
}

void CamControl::setParamCam(float dist, float speedR, float heightC)
{
	this->distanceToObj = dist;
	this->speedRotation = speedR;
	this->heightCamera = heightC;
}

CamControl::~CamControl()
{
	delete this->camera;
}
