#pragma once
#include "ofMain.h"

/** \brief	The size X Map. */
const int sizeMx = 18;

/** \brief	The size Y Map. */
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
		 * \param	load	true to load.
		 **************************************************************************************************/
		MatrixMap(bool load = false);

		/**********************************************************************************************//**
		 * \fn	void MatrixMap::update();
		 *
		 * \brief	Updates this object.
		 **************************************************************************************************/
		void update();

		/**********************************************************************************************//**
		 * \fn	void MatrixMap::draw();
		 *
		 * \brief	Draws this object.
		 **************************************************************************************************/
		void draw();


		/**********************************************************************************************//**
		 * \fn	MatrixMap::~MatrixMap();
		 *
		 * \brief	Destructor.
		 **************************************************************************************************/
		~MatrixMap();

	private:

		bool loadTextur = false;
		ofPlanePrimitive *matrixPlane[sizeMx][sizeMy];
		ofImage *matrixTexture[sizeMx][sizeMy];
};

