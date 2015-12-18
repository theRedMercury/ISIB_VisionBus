#pragma once
#include "ofMain.h"

/** \brief	The size mx. */
const int sizeMx = 18;

/** \brief	The size my. */
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
		 * \fn	ofPlanePrimitive* MatrixMap::getPlaneMap(int i = 0, int j = 0);
		 *
		 * \brief	Gets plane map.
		 *
		 * \param	i	Zero-based index of the.
		 * \param	j	The int to process.
		 *
		 * \return	null if it fails, else the plane map.
		 **************************************************************************************************/
		ofPlanePrimitive* getPlaneMap(int i = 0, int j = 0);

		/**********************************************************************************************//**
		 * \fn	ofImage* MatrixMap::getTextureMap(int i = 0, int j = 0);
		 *
		 * \brief	Gets texture map.
		 *
		 * \param	i	Zero-based index of the.
		 * \param	j	The int to process.
		 *
		 * \return	null if it fails, else the texture map.
		 **************************************************************************************************/
		ofImage* getTextureMap(int i = 0, int j = 0);

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

