#include "ParsingBus.h"

ParsingBus::ParsingBus()
{
	this->urlBus = URLPORTLAND;
	this->posBus = new ofSpherePrimitive();
	this->posBus->setGlobalPosition(ofVec3f(0.0, 0.0, 0.0));
	this->posBus->setPosition(ofVec3f(0.0, 0.0, 0.0));
	
	this->result = new ofxJSONElement();
	this->lockList = new mutex();
	this->updateRun = true;
	this->threadUpdateBus = new thread(&ParsingBus::run, this);

	

	//cent. lon=-122.670188804517, cent. lat=45.5163462318906, zoom=16.6333565146525, lon=-122.670866632315, lat=45.5157937272067	=> 0 - 0
	//cent. lon=-122.731024228244, cent. lat=45.5520580331802, zoom=17.6514510002014, lon=-122.732834284994, lat=45.5523641484565

	//lon=-122.670188804517, cent. lat=45.5163462318906		=>	 0 - 0
	//lon=0.060835423727, cent. lat=0.0357118012896		=>	 1216 - 1472
	//lon=0.060835423727, cent. lat=0.0535677019344		=>	 1216 - 2208
	//lon=0.0912531355905, cent. lat=0.0357118012896		=>	 1824 - 1472
	//lon=-122.731024228244, cent. lat=45.5520580331802		=> 2432 - 2944

	//LON => 2432 px -> 0.060835423727 �	=> 39976.70848671395
	//LAT => 2944 px -> 0.0357118012896 �	=> 82437.73468960672
	//data example
	//cent.lon = -122.678212963494, cent.lat = 45.5131557913187, zoom = 16.6333565146525, lon = -122.680896608249, lat = 45.5127680473194
	
	//float poX = ((-122.731024228244) - -122.670188804517) * 39976.70848671395;
	//float poY = ((45.5163462318906) - 45.5163462318906) * 82437.73468960672;
}

ParsingBus::ParsingBus(string url, int maxB)
{
	
	this->urlBus = url;
	this->maxBus = maxB;
	this->posBus = new ofSpherePrimitive();
	this->posBus->setPosition(ofVec3f(0.0, 0.0, 0.0));
	this->result = new ofxJSONElement();
	this->lockList = new mutex();
	this->updateRun = true;
	this->threadUpdateBus = new thread(&ParsingBus::run, this);

}	

ofVec3f * ParsingBus::getPositionBus(){
	//If no bus
	if (this->indexRandom == -1 || this->listBus->at(this->indexRandom)==nullptr) {
		return  &this->posBus->getPosition();
	}
	return this->listBus->at(this->indexRandom)->getPosBus();
}

string ParsingBus::getDataBus() {
	if (this->indexRandom == -1 || this->listBus->at(this->indexRandom) == nullptr) {
		return  "";
	}
	return this->listBus->at(this->indexRandom)->getData();
}

void ParsingBus::run(){
	ofLogNotice("ofApp::setup") << "Thread start...";

	while (this->updateRun) {

		i = 0;
		idB = 0;
		busData = "";
		busFullData = "";

		try {
			//this->urlBus;
			if (this->result->open("example_output_pretty.json") && !this->result->empty())
			{
				this->maxBusInList = this->result->get("resultSet", "resultSet")["vehicle"].size();
				//Limite Size
				if (this->maxBus < this->maxBusInList) {
					this->maxBusInList = this->maxBus;
				}
				ofLogNotice("ofApp::setup") << "Update : " << this->maxBusInList << " size";

				time_end = clock() + 1000 * CLOCKS_PER_SEC / 1000;
				while (clock() < time_end)
				{
				}
				if (this->maxBusInList > 0) {

					//Init first Time Liste Bus
					if (this->listBus == nullptr) {
						this->listBus = new vector<Bus*>();
						for (int i = 0; i < this->maxBusInList; i++) {

							idB = this->result->get("resultSet", "resultSet")["vehicle"][i]["vehicleID"].asInt();
							busData = this->result->get("resultSet", "resultSet")["vehicle"][i]["type"].asString() + ":" + to_string(idB);
							busFullData = busData + "\n" + this->result->get("resultSet", "resultSet")["vehicle"][i]["signMessage"].asString();
							busFullData += "\n" + this->result->get("resultSet", "resultSet")["vehicle"][i]["signMessageLong"].asString();
							lo = this->result->get("resultSet", "resultSet")["vehicle"][i]["longitude"].asString();
							la = this->result->get("resultSet", "resultSet")["vehicle"][i]["latitude"].asString();

							this->listBus->push_back(new Bus(idB, busData, busFullData,
								-(((atof(lo.c_str())) - -122.670188804517) * 39976.70848671395),
								-(((atof(la.c_str())) - 45.5163462318906) * 82437.73468960672)));
						}
						ofLogNotice("ofApp::setup") << "Bus Create";
					}
					else{
						if (this->maxBusInList > this->listBus->size()) {
							for (int i = 0; i < (this->listBus->size() - this->maxBusInList); i++) {
								this->listBus->push_back(new Bus());
								ofLogNotice("ofApp::setup") << "New Bus";
							}
						}
						//Init False all Bus--------------------------------
						for (int ju = 0; ju < this->listBus->size(); ju++) {
							this->listBus->at(ju)->setExist(false);
						}

						for (int j = 0; j < this->listBus->size(); j++) {
							busData = "";
							idB = this->result->get("resultSet", "resultSet")["vehicle"][j]["vehicleID"].asInt();
							busData = this->result->get("resultSet", "resultSet")["vehicle"][j]["type"].asString() + ":" + to_string(idB);
							busFullData = busData + "\n" + this->result->get("resultSet", "resultSet")["vehicle"][j]["signMessage"].asString();
							busFullData += "\n" + this->result->get("resultSet", "resultSet")["vehicle"][j]["signMessageLong"].asString();
							lo = this->result->get("resultSet", "resultSet")["vehicle"][j]["longitude"].asString();
							la = this->result->get("resultSet", "resultSet")["vehicle"][j]["latitude"].asString();
							i = 0;

							//ofLogNotice("ofApp::setup") << it;idB
							while (i < this->maxBusInList) {
								if (this->listBus->at(i)->getId() == -1) {
									this->listBus->at(i)->setId(idB);
									this->listBus->at(i)->setData(busData);
									this->listBus->at(i)->setFullData(busFullData);
								}
								if (this->listBus->at(i)->getId() == idB) {
									this->listBus->at(i)->setExist(true);
									//ofLogNotice("ofApp::setup") << "Set Poss";
									//float poX = (((atof(lo.c_str())) - -122.670188804517) * 39976.70848671395);
									//float poY = (((atof(la.c_str())) - 45.5163462318906) * 82437.73468960672);

									this->listBus->at(i)->setCoord(-(((atof(lo.c_str())) - -122.670188804517) * 39976.70848671395),
										-(((atof(la.c_str())) - 45.5163462318906) * 82437.73468960672));
									i = this->maxBusInList;//Stop While if Bus Found
								}
								i++;
							}
						}
					}
					this->result->clear();

					//std::sort(this->listBus->begin(), this->listBus->end());
					//Delet bus no update
					this->lockList->lock();
					for (int je = this->listBus->size() - 1; je >= 0; je--) {
						if (!this->listBus->at(je)->getExist()) {
							delete this->listBus->at(je);
							this->listBus->at(je) = nullptr;
							this->listBus->erase(this->listBus->begin() + je);
							//this->listBus->at(je)=nullptr;
							//this->listBus->erase(remove(this->listBus->begin(), this->listBus->end(), this->listBus->at(je)), this->listBus->end());
							//this->listBus->erase(this->listBus->begin() + je);
							//this->listBus->at(je) = this->listBus->back();//move the item in the back to the index
							//this->listBus->pop_back(); //delete the item in the back
						}
					}
					this->lockList->unlock();
					/*for (int je = 0; je < this->listBus->size(); je++) {
						if (!this->listBus->at(je)->getExist()) {
							//this->listBus->at(je)->~Bus();
							try {
								this->listBus->erase(this->listBus->begin() + je);
							}
							catch (...) {
								ofLogError("ofApp::setup") << "Something happened... " << endl;
							}

						}
					}*/
					this->indexRandom = rand() % this->maxBusInList;
				}
			}
			else
			{
				ofLogError("ofApp::setup") << "Failed to parse JSON... :( " << endl;
			}
		}
		//All Error...
		catch (...) {
			ofLogError("ofApp::setup") << "Failed to open JSON... :( " << endl;
		}
		time_end = clock() + 15000 * CLOCKS_PER_SEC / 1000;
		while (clock() < time_end)
		{
		}
	}
}

void ParsingBus::stop() {
	this->updateRun = false;
	this->threadUpdateBus->join();
}

void ParsingBus::draw(bool drag, bool showD){
	if (this->listBus != nullptr) {
		this->lockList->lock();
		for (int i = 0; i < this->listBus->size(); i++) {
			if (this->listBus->at(i) != nullptr) {
				this->listBus->at(i)->draw(drag, showD);
			}
		}
		this->lockList->unlock();
	}
}

ParsingBus::~ParsingBus()
{
	this->stop();

	if (this->listBus != nullptr) {
		this->lockList->lock();
		for (int i = 0; i < this->listBus->size(); i++) {
			delete this->listBus->at(i);
		}
		this->lockList->unlock();
		this->listBus->clear();
		delete this->listBus;
	}
	delete this->posBus;
	delete this->result;

	delete this->lockList;
}
