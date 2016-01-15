#pragma once
#include "ofMain.h"

/** \brief	The number of images X axis. */
const int sizeMx = 18;

/** \brief	The number of images Y axis. */
const int sizeMy = 22;

/**********************************************************************************************//**
 * \class	MatrixMap
 *
 * \brief	A matrix map.
 *
 * \author	Nicolas
 * \date	10/12/2015
 **************************************************************************************************/
class MatrixMap
{
	public:

		/**********************************************************************************************//**
		 * \fn	MatrixMap::MatrixMap(bool load = false);
		 *
		 * \brief	Constructor.
		 * \param	load		load or not images.
		 **************************************************************************************************/
		MatrixMap(bool load = false);

		/**********************************************************************************************//**
		 * \fn	void MatrixMap::update();
		 *
		 * \brief	Updates the map.
		 **************************************************************************************************/
		void update();

		/**********************************************************************************************//**
		 * \fn	void MatrixMap::draw();
		 *
		 * \brief	Draws the map.
		 **************************************************************************************************/
		void draw();


		/**********************************************************************************************//**
		 * \fn	MatrixMap::~MatrixMap();
		 *
		 * \brief	Destructor.
		 **************************************************************************************************/
		~MatrixMap();

	private:

		/** \brief	Bool for load the texture. */
		bool loadTextur = false;					
		ofPlanePrimitive *matrixPlane[sizeMx][sizeMy];
		ofImage *matrixTexture[sizeMx][sizeMy];			
};

