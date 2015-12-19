#pragma once
#include "ofMain.h"

/** \brief	The size maximum history. */
const int sizeMaxHistory = 11;

/**********************************************************************************************//**
* \struct	posXYZBus
*
* \brief	A position xyz bus.
*
* \author	Nicolas
* \date	10/12/2015
**************************************************************************************************/
struct  posXYZBus
{
	float x;
	float y;
	float z;
};

/**********************************************************************************************//**
 * \class	Bus
 *
 * \brief	A bus.
 *
 * \author	Nicolas
 * \date	10/12/2015
 **************************************************************************************************/
class Bus
{

	public:

		/**********************************************************************************************//**
		 * \fn	Bus::Bus();
		 *
		 * \brief	Default constructor.
		 **************************************************************************************************/
		Bus();

		Bus(int id, string d, string dat, float fx, float fy);

		/**********************************************************************************************//**
		 * \fn	int Bus::getId();
		 *
		 * \brief	Gets the identifier.
		 *
		 * \return	The identifier.
		 **************************************************************************************************/
		int getId();

		/**********************************************************************************************//**
		 * \fn	bool Bus::getExist();
		 *
		 * \brief	Gets the exist.
		 *
		 * \return	true if it succeeds, false if it fails.
		 **************************************************************************************************/
		bool getExist();

		/**********************************************************************************************//**
		 * \fn	ofVec3f Bus::*getPosBus();
		 *
		 * \brief	Gets position bus.
		 *
		 * \return	null if it fails, else the position bus.
		 **************************************************************************************************/
		ofVec3f *getPosBus();

	
		/**********************************************************************************************//**
		 * \fn	string Bus::getData();
		 *
		 * \brief	Gets the data.
		 *
		 * \return	The data.
		 **************************************************************************************************/
		string getData();

		/**********************************************************************************************//**
		 * \fn	void Bus::setId(int id);
		 *
		 * \brief	Sets an identifier.
		 *
		 * \param	id	The identifier.
		 **************************************************************************************************/
		void setId(int id);

		/**********************************************************************************************//**
		 * \fn	void Bus::setRadius(float i = 6.0);
		 *
		 * \brief	Sets the radius.
		 *
		 * \param	i	Zero-based index of the.
		 **************************************************************************************************/
		void setRadius(float i = 6.0);

		/**********************************************************************************************//**
		 * \fn	void Bus::setCoord(float x = 0.0, float y = 0.0);
		 *
		 * \brief	Sets a coordinate.
		 *
		 * \param	x	The x coordinate.
		 * \param	y	The y coordinate.
		 **************************************************************************************************/
		void setCoord(float x = 0.0, float y = 0.0);

		/**********************************************************************************************//**
		 * \fn	void Bus::setData(string dat="");
		 *
		 * \brief	Sets a data.
		 *
		 * \param	dat	The dat.
		 **************************************************************************************************/
		void setData(string dat="");

		/**********************************************************************************************//**
		 * \fn	void Bus::setFullData(string fDat = "");
		 *
		 * \brief	Sets full data.
		 *
		 * \param	fDat	The dat.
		 **************************************************************************************************/
		void setFullData(string fDat = "");

		/**********************************************************************************************//**
		 * \fn	void Bus::setBlur(bool b = true);
		 *
		 * \brief	Sets a blur.
		 *
		 * \param	b	true to b.
		 **************************************************************************************************/
		void setBlur(bool b = true);

		/**********************************************************************************************//**
		 * \fn	void Bus::setExist(bool e = true);
		 *
		 * \brief	Sets an exist.
		 *
		 * \param	e	true to e.
		 **************************************************************************************************/
		void setExist(bool e = true);

		/**********************************************************************************************//**
		 * \fn	void Bus::update();
		 *
		 * \brief	Updates this object.
		 **************************************************************************************************/
		void update();

		/**********************************************************************************************//**
		 * \fn	void Bus::draw(bool drag=true, bool showDat = true);
		 *
		 * \brief	Draws.
		 * 			
		 * \param	drag   	true to drag.
		 * \param	showDat	true to show, false to hide the dat.
		 **************************************************************************************************/
		void draw(bool drag=true, bool showDat = true);

		/**********************************************************************************************//**
		 * \fn	Bus::~Bus();
		 *
		 * \brief	Destructor.
		 **************************************************************************************************/
		~Bus();

	private:
		
		bool exist = true;
		bool blur = true;
		int idBus = -1;
		int noMove = 1;
		float animBus = 1.0;
		float radiusB = 4.0;
		string dataBus = "Data";
		string fullDataBus = "Data";
		mutex *mutLock;

		//Data OpenFrameWorks
		ofSpherePrimitive *sphereBus;
		ofPolyline *lineBus;
		ofSpherePrimitive *effecBlur[8];

		//Data Coord
		int sizeHistPos = 0;
		posXYZBus *historyPos[sizeMaxHistory];
};

