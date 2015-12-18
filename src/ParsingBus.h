#pragma once
#include <thread>
#include <time.h>
#include <cstdlib>

#include "Bus.h"
#include "ofMain.h"
#include "ofxJSON\src\ofxJSON.h"

#define URLPORTLAND "https://developer.trimet.org/ws/v2/vehicles/locIDs/6849,6850/appID/57CDC57DB4E60BE1AA0A100E2"

/**********************************************************************************************//**
 * \class	ParseBus
 *
 * \brief	A parse bus.
 *
 * \author	Nicolas
 * \date	10/12/2015
 **************************************************************************************************/
using namespace std;
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


		string urlBus = "";
		int maxBus = 250;
		int maxBusInList = 0;
		int indexRandom = -1;
		bool updateRun = false;
		bool drawing = true;
		

		int i;
		int idB;
		string busData;
		string busFullData;
		string la;
		string lo;
		clock_t time_end;

		mutex * lockList = nullptr;
		thread * threadUpdateBus = nullptr;
		vector<Bus*> * listBus = nullptr;
		ofSpherePrimitive * posBus = nullptr;
		ofxJSONElement * result = nullptr;
			
};

