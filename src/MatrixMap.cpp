#include "MatrixMap.h"

MatrixMap::MatrixMap(bool load)
{
	this->loadTextur = load;
	if (this->loadTextur){
		for (int i = 0; i < sizeMx; i++) {
			for (int j = 0; j < sizeMy; j++) {

				string imgPath = "map/" + ofToString(i + 1) + "." + ofToString(j + 1) + ".png";
				int sizePlane = 256;

				this->matrixTexture[i][j] = new ofImage(imgPath);
				this->matrixTexture[i][j]->mirror(true, false);
				this->matrixPlane[i][j] = new ofPlanePrimitive();
				this->matrixPlane[i][j]->setHeight(sizePlane);
				this->matrixPlane[i][j]->setWidth(sizePlane);
				this->matrixPlane[i][j]->setPosition(((j*sizePlane) - (((sizeMy / 2) * sizePlane))), ((((sizeMx / 2)* sizePlane) - (i*sizePlane))), 0);
				this->matrixPlane[i][j]->enableTextures();
			}
		}
	}
}

void MatrixMap::update() {
	//ofSetColor(ofColor::fromHex(0x444546));
	if (this->loadTextur) {
		for (int i = 0; i < sizeMx; i++) {
			for (int j = 0; j < sizeMy; j++) {
				this->matrixTexture[i][j]->update();
			}
		}
	}
}

void MatrixMap::draw() {
	if (this->loadTextur) {
		ofSetColor(255, 255, 255);
		//ofSetColor(ofColor::fromHex(0x444546));
		for (int i = 0; i < sizeMx; i++) {
			for (int j = 0; j < sizeMy; j++) {
				this->matrixTexture[i][j]->getTextureReference().bind();
				this->matrixPlane[i][j]->draw();
				this->matrixTexture[i][j]->getTextureReference().unbind();
			}
		}
	}
}


MatrixMap::~MatrixMap()
{
	if (this->loadTextur) {
		for (int i = 0; i < sizeMx; i++) {
			for (int j = 0; j < sizeMy; j++) {
				this->matrixTexture[i][j]->clear();
				delete this->matrixTexture[i][j];
				delete this->matrixPlane[i][j];
			}
		}
		
		//delete[] this->matrixTexture;
		//delete[] this->matrixPlane;
	}
}
