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

	//LON => 2432 px -> 0.060835423727 °	=> 39976.70848671395
	//LAT => 2944 px -> 0.0357118012896 °	=> 82437.73468960672
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
	int ind;
	while (this->updateRun) {

		ind = 0;
		idB = 0;
		busData = "";
		busFullData = "";

		try {
			if (this->result->open(this->urlBus) && !this->result->empty())
			{
				this->maxBusInList = this->result->get("resultSet", "resultSet")["vehicle"].size();
				//Limite Size
				if (this->maxBus < this->maxBusInList) {
					this->maxBusInList = this->maxBus;
				}
				ofLogNotice("ofApp::setup") << "Number of bus : " << this->maxBusInList;
				this->sleepThread(1000);
				
				if (this->maxBusInList > 0) {

					//Init first Time Liste Bus
					if (this->listBus == nullptr) {
						//this->lockList->lock();
						this->listBus = new vector<Bus*>();
						for (int i = 0; i < this->maxBusInList; i++) {

							idB = this->result->get("resultSet", "resultSet")["vehicle"][i]["vehicleID"].asInt();
							busData = this->result->get("resultSet", "resultSet")["vehicle"][i]["type"].asString();
							this->listBus->push_back(new Bus(idB,
								busData + ":" + to_string(idB),
								busData + ":" + to_string(idB) + "\n" + this->result->get("resultSet", "resultSet")["vehicle"][i]["signMessage"].asString()
								+ "\n" + this->result->get("resultSet", "resultSet")["vehicle"][i]["signMessageLong"].asString(),
								-(((atof(this->result->get("resultSet", "resultSet")["vehicle"][i]["longitude"].asString().c_str())) - -122.670188804517) * 39976.70848671395),
								-(((atof(this->result->get("resultSet", "resultSet")["vehicle"][i]["latitude"].asString().c_str())) - 45.5163462318906) * 82437.73468960672)));

						}
						//this->lockList->unlock();
						ofLogNotice("ofApp::setup") << this->maxBusInList << " create bus";
					}

					else{
						if (this->maxBusInList > this->listBus->size()) {
							//this->lockList->lock();
							for (int i = 0; i < (this->listBus->size() - maxBus); i++) {
								this->listBus->push_back(new Bus());
								ofLogNotice("ofApp::setup") << "Add new Bus";
							}
							//this->lockList->unlock();
						}
						//Init False all Bus--------------------------------
						//this->lockList->lock();
						for (int ju = 0; ju < this->maxBusInList; ju++) {
							this->listBus->at(ju)->setExist(false);
						}
						//this->lockList->unlock();

						for (int j = 0; j < this->listBus->size(); j++) {
							idB = this->result->get("resultSet", "resultSet")["vehicle"][j]["vehicleID"].asInt();
							busData = this->result->get("resultSet", "resultSet")["vehicle"][j]["type"].asString() + ":" + to_string(idB);
							busFullData = busData + "\n" + this->result->get("resultSet", "resultSet")["vehicle"][j]["signMessage"].asString();
							busFullData += "\n" + this->result->get("resultSet", "resultSet")["vehicle"][j]["signMessageLong"].asString();
							lo = this->result->get("resultSet", "resultSet")["vehicle"][j]["longitude"].asString();
							la = this->result->get("resultSet", "resultSet")["vehicle"][j]["latitude"].asString();
							
							ind = 0;

							while (ind < this->maxBusInList) {
								//this->lockList->lock();
								if (this->listBus->at(ind)->getId() == -1) {
									this->listBus->at(ind)->setId(idB);
									this->listBus->at(ind)->setData(busData);
									this->listBus->at(ind)->setFullData(busFullData);
								}
								if (this->listBus->at(ind)->getId() == idB) {
									this->listBus->at(ind)->setExist(true);
									//float poX = (((atof(lo.c_str())) - -122.670188804517) * 39976.70848671395);
									//float poY = (((atof(la.c_str())) - 45.5163462318906) * 82437.73468960672);
									
									this->listBus->at(ind)->setCoord(-(((atof(lo.c_str())) - this->longi) * this->longiMulti),
										-(((atof(la.c_str())) - this->latit) * this->latitMulti));
									
									ind = this->maxBusInList;//Stop While if Bus Found
								}
								//this->lockList->unlock();
								ind++;
							}
						}
					}
					this->result->clear();

					//Delet bus no update
					this->lockList->lock();
					for (int je = this->listBus->size() - 1; je >= 0; je--) {
						if (!this->listBus->at(je)->getExist()) {
							delete this->listBus->at(je);
							this->listBus->erase(this->listBus->begin() + je);
							//this->listBus->at(je) = nullptr;
						}
					}
					this->lockList->unlock();
					this->indexRandom = rand() % this->maxBusInList;
				}
			}
			else
			{
				ofLogError("ofApp::setup") << "Failed to parse JSON... :( " << endl;
			}
		}
		//All Error...
		catch (const std::exception& e) {
			ofLogError("ofApp::setup") << "FATA ERROR " << e.what() << endl;
		}
		catch (...) {
			ofLogError("ofApp::setup") << "Failed to open JSON... :( "  << endl;
		}
		this->sleepThread(15000);
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

void ParsingBus::sleepThread(int msTime) {
	clock_t timeEnd = clock() + msTime * CLOCKS_PER_SEC / 1000;
	while (clock() < timeEnd)
	{
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
