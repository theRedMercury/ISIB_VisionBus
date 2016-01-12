#pragma once
#include "ofMain.h"

#define PI 3.14159265
#define GROUND 8.0

/**********************************************************************************************//**
 * \class	CamControl
 *
 * \brief	A camera control.
 *
 * \author	Nicolas
 * \date	10/12/2015
 **************************************************************************************************/
class CamControl
{
	public:

		/**********************************************************************************************//**
		 * \fn	CamControl::CamControl();
		 *
		 * \brief	Default constructor.
		 **************************************************************************************************/
		CamControl();

		/**********************************************************************************************//**
		* \fn	void CamControl::backForwardCam(float v);
		*
		* \brief	Back Forward Camera
		* \param	v   	The value to move.
		**************************************************************************************************/
		void backForwardCam(float v);

		/**********************************************************************************************//**
		* \fn	void CamControl::leftRightCam(float v);
		*
		* \brief	Left Right Camera
		* \param	v   	The value to move.
		**************************************************************************************************/
		void leftRightCam(float v);

		/**********************************************************************************************//**
		* \fn	void CamControl::slideUpDown(float v);
		*
		* \brief	Slide Up Down Camera
		* \param	v   	The value to move.
		**************************************************************************************************/
		void slideUpDown(float v);

		/**********************************************************************************************//**
		* \fn	void CamControl::rotatCam(float v);
		*
		* \brief	Rotation of Camera
		* \param	v   	The value to move.
		**************************************************************************************************/
		void rotatCam(float v);

		/**********************************************************************************************//**
		* \fn	void CamControl::rotateUpDownCam(float v);
		*
		* \brief	Rotatation Up Down Camera
		* \param	v   	The value to move.
		**************************************************************************************************/
		void rotateUpDownCam(float v);

		/**********************************************************************************************//**
		* \fn	void CamControl::rotateLeftRightCam(float v);
		*
		* \brief	Rotatation Left Right  Camera
		* \param	v   	The value to move.
		**************************************************************************************************/
		void rotateLeftRightCam(float v);

		/**********************************************************************************************//**
		 * \fn	float CamControl::getSpeedRotation();
		 *
		 * \brief	Gets speed rotation.
		 * \return	The speed rotation.
		 **************************************************************************************************/
		float getSpeedRotation();

		/**********************************************************************************************//**
		 * \fn	float CamControl::getHeightCamera();
		 *
		 * \brief	Gets height camera.	
		 * \return	The height camera.
		 **************************************************************************************************/
		float getHeightCamera();

		/**********************************************************************************************//**
		 * \fn	float CamControl::getDistanceToObj();
		 *
		 * \brief	Gets distance to object.
		 * \return	The distance to object.
		 **************************************************************************************************/
		float getDistanceToObj();

		/**********************************************************************************************//**
		 * \fn	void CamControl::setParamCam(float dist, float speedR, float heightC);
		 *
		 * \brief	Sets parameter camera.
		 * \param	dist   	The distance.
		 * \param	speedR 	The speed r.
		 * \param	heightC	The height c.
		 **************************************************************************************************/
		void setParamCam(float dist, float speedR, float heightC);

		/**********************************************************************************************//**
		* \fn	void CamControl::update(ofVec3f data);
		*
		* \brief	Updates the given data.
		* \param [in,out]	data	If non-null, the data.
		**************************************************************************************************/
		void update(ofVec3f data);

		/**********************************************************************************************//**
		 * \fn	void CamControl::camBegin();
		 *
		 * \brief	Camera begin.
		 **************************************************************************************************/
		void camBegin();

		/**********************************************************************************************//**
		 * \fn	void CamControl::camEnd();
		 *
		 * \brief	Camera end.
		 **************************************************************************************************/
		void camEnd();

		/**********************************************************************************************//**
		 * \fn	CamControl::~CamControl();
		 *
		 * \brief	Destructor.
		 **************************************************************************************************/
		~CamControl();

	private:

		float speedRotation = 0.2;
		float heightCamera = 1.0;
		float distanceToObj = 350.0;

		float rot = 0.0;
		ofEasyCam * camera;
};

