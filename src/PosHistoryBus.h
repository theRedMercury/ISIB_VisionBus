#pragma once
#include "ofMain.h"

#include <mutex>
#include <condition_variable>


/** \brief	The size history. */
const int sizeHistory = 11;

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
 * \class	PosHistoryBus
 *
 * \brief	A position history bus.
 *
 * \author	Nicolas
 * \date	10/12/2015
 **************************************************************************************************/
class PosHistoryBus	
{
	public:

		/**********************************************************************************************//**
		 * \fn	PosHistoryBus::PosHistoryBus();
		 *
		 * \brief	Default constructor.
		 **************************************************************************************************/
		PosHistoryBus();

		/**********************************************************************************************//**
		 * \fn	int PosHistoryBus::getSizeMax();
		 *
		 * \brief	Gets size maximum.
		 *
		 * \return	The calculated size maximum.
		 **************************************************************************************************/
		int getSizeMax();

		/**********************************************************************************************//**
		 * \fn	void PosHistoryBus::pushPos(float x, float y, float z);
		 *
		 * \brief	Pushes a position.
		 *
		 * \param	x	The x coordinate.
		 * \param	y	The y coordinate.
		 * \param	z	The z coordinate.
		 **************************************************************************************************/
		void pushPos(float x, float y, float z);

		/**********************************************************************************************//**
		 * \fn	posXYZBus* PosHistoryBus::get(int i=0);
		 *
		 * \brief	Gets a position xyz bus* using the given i.
		 *
		 * \param	i	The i to get.
		 *
		 * \return	null if it fails, else a posXYZBus*.
		 **************************************************************************************************/
		posXYZBus* get(int i=0);

		/**********************************************************************************************//**
		 * \fn	PosHistoryBus::~PosHistoryBus();
		 *
		 * \brief	Destructor.
		 **************************************************************************************************/
		~PosHistoryBus();

	private : 
		std::mutex mtxBus;
		bool canRead = true;
		int sizeMax = 0;
		posXYZBus *HistoPos[sizeHistory];
};

