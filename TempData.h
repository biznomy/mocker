/*
 * TempData.h
 *
 *  Created on: 12-Sep-2017
 *      Author: ubuntu
 */

#ifndef OTFS_SRC_APP_DASHBOARD_TEST_TEMPDATA_H_
#define OTFS_SRC_APP_DASHBOARD_TEST_TEMPDATA_H_
#include "mocker.h"
#include "wirelessTrue.h"
#include "wirelessFalse.h"

#include "cpu.h"
#include "system.h"

#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"
#include "Poco/Util/Application.h"
#include "Poco/Timestamp.h"
using Poco::JSON::Parser;
using Poco::JSON::Object;
using Poco::JSON::Array;
using Poco::Dynamic::Var;
using Poco::Util::Application;

#include "Poco/DateTime.h"
#include "Poco/Util/JSONConfiguration.h"
#include "Poco/AutoPtr.h"

class TempData{

private :
	TempData();
	TempData(std::string path);
	static TempData *s_instance;
	static Poco::AutoPtr<Poco::Util::JSONConfiguration> instanceConf(std::string);
	void getWirelessTrue(Poco::JSON::Object &object);
	void getWirelessFalse(Poco::JSON::Object &object);
	void getSystem(Poco::JSON::Object &object);
	void getIpv4(Poco::JSON::Object &object);
	void getSystemInfo(Poco::JSON::Object &object);

public :
	Poco::DateTime date;
	virtual ~TempData();
	static TempData *instance();
	Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf ;
	void generateInteger(Poco::JSON::Object &object, std::string key, int lower, int upper, int fluctuation);
	void generateFloat(Poco::JSON::Object &object, std::string key, float lower, float upper, float fluctuation);
	void generateLong(Poco::JSON::Object &object, std::string key, long lower, long upper, long fluctuation);
	void generateDouble(Poco::JSON::Object &object, std::string key, double lower, double upper, double fluctuation);
	void getData(Poco::JSON::Object &object);

};

TempData *TempData::s_instance = 0;

/**
 * load configuration file to generate data ONCE only
 * @param path
 * @return
 */
Poco::AutoPtr<Poco::Util::JSONConfiguration> TempData::instanceConf(std::string path) {
	Poco::AutoPtr<Poco::Util::JSONConfiguration> temp;
		try{
			temp = new Poco::Util::JSONConfiguration(path);
		}catch(Poco::Exception &e){
			std::cout << e.displayText()<< std::endl;
		}
	return temp;
}

/**
 *	Create Singleton instance
 * @return instance(singleton) of Class
 */
TempData *TempData::instance() {
	if (!s_instance){
		s_instance = new TempData("/opt/otfs/install/etc/mocker.9.X.json");
	}
	return s_instance;
}

TempData::TempData() {

}

TempData::TempData(std::string path) {
	try{
		pConf = TempData::instanceConf(path);
	}catch(Poco::Exception &e){
		cout << Poco::format("File Exception Occur:  %s", e.displayText()) << endl;
	}
}

TempData::~TempData() {
//	cout << "close object tempData" << endl;
}

/**
 * param [&object : Poco::JSON::Object address]
 * param [key : std:string]
 * param [lower : int -> lowest possible value]
 * param [upper : int -> upper possible value]
 * param [fluctuation : int -> fluctuation (around mean: (lower+upper)/2) possible value]
 * return void
 **/
void TempData::generateInteger(Poco::JSON::Object &object, std::string key, int lower, int upper, int fluctuation){
	object.set(key, Mocker::getRandomMeanInteger(lower, upper, fluctuation));
}
/**
 * param [&object : Poco::JSON::Object address]
 * param [key : std:string]
 * param [lower : float -> lowest possible value]
 * param [upper : float -> upper possible value]
 * param [fluctuation : float -> fluctuation (around mean: (lower+upper)/2) possible value]
 * return void
 **/
void TempData::generateFloat(Poco::JSON::Object &object, std::string key, float lower, float upper, float fluctuation){
	object.set(key, Mocker::getRandomMeanFloat(lower, upper, fluctuation));
}
/**
 * param [&object : Poco::JSON::Object address]
 * param [key : std:string]
 * param [lower : long -> lowest possible value]
 * param [upper : long -> upper possible value]
 * param [fluctuation : long -> fluctuation (around mean: (lower+upper)/2) possible value]
 * return void
 **/
void TempData::generateLong(Poco::JSON::Object &object, std::string key, long lower, long upper, long fluctuation){
	object.set(key, Mocker::getRandomMeanLong(lower, upper, fluctuation));
}
/**
 * param [&object : Poco::JSON::Object address]
 * param [key : std:string]
 * param [lower : double -> lowest possible value]
 * param [upper : double -> upper possible value]
 * param [fluctuation : double -> fluctuation (around mean: (lower+upper)/2) possible value]
 * return void
 **/
void TempData::generateDouble(Poco::JSON::Object &object, std::string key, double lower, double upper, double fluctuation){
	object.set(key, Mocker::getRandomMeanDouble(lower, upper, fluctuation));
}


/**
 * load wireless true data from getWirelessTrue and
 * set to key wireless and set to param JSON object
 * @param object
 */
void TempData::getWirelessTrue(Poco::JSON::Object &object){
	WirelessTrue wirelessTrue;
	Poco::JSON::Object wireless;
	wirelessTrue.getWirelessTrue(wireless, this->pConf);
	object.set("wireless", wireless);
}

/**
 * load wireless false data from getWirelessFalse and
 * set to key wireless and set to param JSON object
 * @param object
 */
void TempData::getWirelessFalse(Poco::JSON::Object &object){
	WirelessFalse wirelessFalse;
	Poco::JSON::Object wireless;
	wirelessFalse.getWirelessFalse(wireless, this->pConf);
	object.set("wireless", wireless);
}

/**
 * load system data from configuration variable and
 * set to key system-sw and set to param JSON object
 * @param object
 */
void TempData::getSystem(Poco::JSON::Object &object){
	Poco::JSON::Object board;
	board.set("board-version", this->pConf->getString("system-board.board-version"));
	object.set("system-board", board);

	Poco::JSON::Object sw;
	sw.set("running-sw-version", this->pConf->getString("system-sw.running-sw-version"));
	object.set("system-sw", sw);
}

/**
 * load network data from configuration variable and
 * set to keys and set to param JSON object
 * @param object
 */
void TempData::getIpv4(Poco::JSON::Object &object){

	object.set("address", this->pConf->getString("ipv4.address"));
	object.set("subnet-mask", this->pConf->getString("ipv4.subnet-mask"));

}

/**
 * load ram, cpu amd disk info
 * @param object
 */
void TempData::getSystemInfo(Poco::JSON::Object &object){
	printRamInfo(object);
	cpuStatus(object);
	printSysDsk(object);
}

/**
 * overall data for wireless true/false, system, memory, inter-net address
 * @param object
 */
void TempData::getData(Poco::JSON::Object &object){
	object.set("connection-pii", this->pConf->getString("connection-pii"));
	object.set("throughput-beam-capacity", this->pConf->getString("throughput-beam-capacity"));
	object.set("throughput-max-capacity", this->pConf->getString("throughput-max-capacity"));

	Poco::Timestamp now;
	long time_value = now.epochTime() * 1000;

	object.set("time", time_value);

	Poco::JSON::Object ipv4;
	this->getIpv4(ipv4);
	object.set("ipv4", ipv4);

	this->getSystem(object);


	Poco::JSON::Object sysinfo;
	this->getSystemInfo(sysinfo);
	object.set("sysInfoFalse", sysinfo);

	Poco::JSON::Object wirelessFalse;
	this->getWirelessFalse(wirelessFalse);
	object.set("wirelessFalse", wirelessFalse);

	Poco::JSON::Object wirelessTrue;
	this->getWirelessTrue(wirelessTrue);
	object.set("wirelessTrue", wirelessTrue);


}




#endif /* OTFS_SRC_APP_DASHBOARD_TEST_TEMPDATA_H_ */

