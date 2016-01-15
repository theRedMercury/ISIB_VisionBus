#pragma once
#include <thread>
#include <time.h>
#include <cstdlib>

#include "Bus.h"
#include "ofMain.h"
#include "ofxJSON\src\ofxJSON.h"

#define URLPORTLAND "https://developer.trimet.org/ws/v2/vehicles/locIDs/6849,6850/appID/XXXXXXXXXXXXXXXXXXXXXXXXX"
#define LONG "-122.670188804517f"
#define LONGMULT "39976.70848671395f"
#define LATI " 45.5163462318906f"
#define LATIMULT "82437.73468960672f"

using namespace std;

/**********************************************************************************************//**
 * \class	ParseBus
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
		 * \fn	ParseBus::ParseBus();
		 *
		 * \brief	Default constructor.
		 **************************************************************************************************/
		ParsingBus();
		
		/**********************************************************************************************//**
		* \fn	ParseBus::ParseBus(string url, int maxB);
		*
		* \brief	Default constructor.
		**************************************************************************************************/
		ParsingBus(string url, int maxB);

		/**********************************************************************************************//**
		 * \fn	void ParseBus::run();
		 *
		 * \brief	Runs this object.
		 **************************************************************************************************/
		void run();

		/**********************************************************************************************//**
		 * \fn	void ParseBus::draw(bool drag = true, bool showDat = true);
		 *
		 * \brief	Draws.
		 *
		 * \param	drag   	true to drag.
		 * \param	showDat	true to show, false to hide the dat.
		 **************************************************************************************************/
		void draw(bool drag = true, bool showDat = true);

		/**********************************************************************************************//**
		 * \fn	void ParseBus::stop();
		 *
		 * \brief	Stops this object.
		 **************************************************************************************************/
		void stop();

		/**********************************************************************************************//**
		 * \fn	ofVec3f * ParseBus::getPositionBus();
		 *
		 * \brief	Gets position bus.
		 *
		 * \return	null if it fails, else the position bus.
		 **************************************************************************************************/
		ofVec3f *  getPositionBus();


		/**********************************************************************************************//**
		 * \fn	string ParseBus::getDataBus();
		 *
		 * \brief	Gets data bus.
		 *
		 * \return	The data bus.
		 **************************************************************************************************/
		string getDataBus();

		/**********************************************************************************************//**
		 * \fn	ParseBus::~ParseBus();
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

