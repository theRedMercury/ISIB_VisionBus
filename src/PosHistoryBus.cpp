#include "PosHistoryBus.h"

PosHistoryBus::PosHistoryBus()
{
	for (int i = sizeHistory-1; i > -1; i--) {	
		this->HistoPos[i] = NULL;
	}
}
int PosHistoryBus::getSizeMax() {
	return this->sizeMax;
}

void PosHistoryBus::pushPos(float x, float y, float z) {

	posXYZBus *pos = new posXYZBus();
	pos->x = x;
	pos->y = y;
	pos->z = z;

	this->canRead = false;
	mtxBus.lock();
	for (int i = sizeHistory-1; i > -1; i--) {
		this->HistoPos[i] = this->HistoPos[i - 1];
	}
	if (this->HistoPos[sizeHistory - 1] != NULL)
	{
		delete this->HistoPos[sizeHistory - 1];
	}
	this->HistoPos[0] = pos;

	if (sizeMax < (sizeHistory-1)) {
		sizeMax += 1;
	}
	mtxBus.unlock();
	this->canRead = true;
}

posXYZBus* PosHistoryBus::get(int i) {
	if (this->canRead) {
		return this->HistoPos[i];
	}return NULL;
}

PosHistoryBus::~PosHistoryBus()
{
	for (int i = sizeHistory-1; i > -1; i--) {
			delete this->HistoPos[i];
	}
	delete this->HistoPos;
}
