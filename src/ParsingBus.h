#pragma once
#include <thread>
#include <time.h>
#include <cstdlib>

#include "Bus.h"
#include "ofMain.h"
#include "ofxJSON\src\ofxJSON.h"

#define URLPORTLAND "https://developer.trimet.org/ws/v2/vehicles/locIDs/6849,6850/appID/XXXXXXXXXXXXXXXXXXXXXXXXX"

using namespace std;

/**********************************************************************************************//**
 * \class	ParsingBus
 *
 * \brief	A parse bus.
 *
 * \author	Nicolas
 * \date	10/12/2015
 **************************************************************************************************/
class ParsingBus
{
	public:

		/**********************************************************************************************//**
		 * \fn	ParsingBus::ParsingBus();
		 *
		 * \brief	Default constructor.
		 **************************************************************************************************/
		ParsingBus();
		
		/**********************************************************************************************//**
		* \fn	ParsingBus::ParsingBus(string url, int maxB);
		*
		* \brief	Default constructor.
		**************************************************************************************************/
		ParsingBus(string url, int maxB);

		/**********************************************************************************************//**
		 * \fn	void ParsingBus::run();
		 *
		 * \brief	Run the thread for parsing.
		 **************************************************************************************************/
		void run();

		/**********************************************************************************************//**
		 * \fn	void ParsingBus::draw(bool drag = true, bool showDat = true);
		 *
		 * \brief	Draws.
		 *
		 * \param	drag   	true to drag.
		 * \param	showDat	true to show, false to hide the dat.
		 **************************************************************************************************/
		void draw(bool drag = true, bool showDat = true);

		/**********************************************************************************************//**
		* \fn	void ParsingBus::setLockBus(bool v = false);
		*
		* \brief	Lock camera for one bus.
		*
		* \param	c   	true to lock camera on the bus.
		**************************************************************************************************/
		void setLockBus(bool v = false);

		/**********************************************************************************************//**
		* \fn	void ParsingBus::getLockBus();
		*
		* \brief	Get if camera is lock or not.
		**************************************************************************************************/
		bool getLockBus();

		/**********************************************************************************************//**
		* \fn	void ParsingBus::newRandIndexBus();
		*
		* \brief	Generate new index for looking camera.
		**************************************************************************************************/
		void newRandIndexBus();

		/**********************************************************************************************//**
		 * \fn	void ParsingBus::stop();
		 *
		 * \brief	Stops this object.
		 **************************************************************************************************/
		void stop();

		/**********************************************************************************************//**
		 * \fn	ofVec3f * ParsingBus::getPositionBus();
		 *
		 * \brief	Gets position bus.
		 *
		 * \return	ofVec3f		XYZ Position.
		 **************************************************************************************************/
		ofVec3f *  getPositionBus();


		/**********************************************************************************************//**
		 * \fn	string ParsingBus::getDataBus();
		 *
		 * \brief	Gets data bus.
		 *
		 * \return	The data of the bus.
		 **************************************************************************************************/
		string getDataBus();

		/**********************************************************************************************//**
		 * \fn	ParsingBus::~ParsingBus();
		 *
		 * \brief	Destructor.
		 **************************************************************************************************/
		~ParsingBus();

	private:
		void sleepThread(int msTime = 1000);

		float  longi = -122.670188804517;
		float  longiMulti = 39976.70848671395;
		float  latit = 45.5163462318906;
		float  latitMulti  = 82437.73468960672;

		string urlBus = "";
		int maxBus = 250;
		int maxBusInList = 0;
		int indexRandom = -1;
		bool updateRun = false;
		bool drawing = true;
		bool lockBus = false;
		

		int idB;
		string busData;
		string busFullData;
		string la;
		string lo;

		mutex * lockList = nullptr;
		thread * threadUpdateBus = nullptr;
		vector<Bus*> * listBus = nullptr;
		ofVec3f * posBusNull = nullptr;
		ofxJSONElement * result = nullptr;
};

