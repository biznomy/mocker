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
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"
#include "Poco/Util/Application.h"

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

Poco::AutoPtr<Poco::Util::JSONConfiguration> TempData::instanceConf(std::string path) {
	Poco::AutoPtr<Poco::Util::JSONConfiguration> temp;
		try{
			temp = new Poco::Util::JSONConfiguration(path);
		}catch(Poco::Exception &e){
			std::cout << e.displayText()<< std::endl;
		}
	return temp;
}


TempData *TempData::instance() {
	if (!s_instance){
		s_instance = new TempData("/opt/otfs/install/etc/mocker.8.X.json");
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



void TempData::getWirelessTrue(Poco::JSON::Object &object){
	WirelessTrue wirelessTrue;
	Poco::JSON::Object wireless;
	wirelessTrue.getWirelessTrue(wireless, this->pConf);
	object.set("wireless", wireless);
}

void TempData::getWirelessFalse(Poco::JSON::Object &object){
	WirelessFalse wirelessFalse;
	Poco::JSON::Object wireless;
	wirelessFalse.getWirelessFalse(wireless);
	object.set("wireless", wireless);
}

void TempData::getSystem(Poco::JSON::Object &object){
	Poco::JSON::Object board;
	board.set("board-version", "2B");
	object.set("system-board", board);

	Poco::JSON::Object sw;
	sw.set("running-sw-version", "8.4.6");
	object.set("system-sw", sw);
}

void TempData::getIpv4(Poco::JSON::Object &object){

	object.set("address", "10.4.128.212");
	object.set("subnet-mask", "255.255.255.0");

}

void TempData::getData(Poco::JSON::Object &object){
	object.set("connection-pii", "locked");
	object.set("time", "1506401045000");

	Poco::JSON::Object ipv4;
	this->getIpv4(ipv4);
	object.set("ipv4", ipv4);

	this->getSystem(object);

	Poco::JSON::Object wirelessFalse;
	this->getWirelessFalse(wirelessFalse);
	object.set("wirelessFalse", wirelessFalse);

	Poco::JSON::Object wirelessTrue;
	this->getWirelessTrue(wirelessTrue);
	object.set("wirelessTrue", wirelessTrue);


}




#endif /* OTFS_SRC_APP_DASHBOARD_TEST_TEMPDATA_H_ */

