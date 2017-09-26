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

public :
	Poco::DateTime date;
	virtual ~TempData();
	static TempData *instance();
	Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf ;
	void generateInteger(Poco::JSON::Object &object, std::string key, int lower, int upper, int fluctuation);
	void generateFloat(Poco::JSON::Object &object, std::string key, float lower, float upper, float fluctuation);
	void generateLong(Poco::JSON::Object &object, std::string key, long lower, long upper, long fluctuation);
	void generateDouble(Poco::JSON::Object &object, std::string key, double lower, double upper, double fluctuation);
	void getWirelessTrue(Poco::JSON::Object &object);
	void getWirelessFalse(Poco::JSON::Object &object);
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
		s_instance = new TempData("/opt/otfs/install/etc/mocker_conf_8383.json");
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
	wirelessTrue.getWirelessTrue(object);
}

void TempData::getWirelessFalse(Poco::JSON::Object &object){
	WirelessFalse wirelessFalse;
	wirelessFalse.getWirelessFalse(object);
}




#endif /* OTFS_SRC_APP_DASHBOARD_TEST_TEMPDATA_H_ */

