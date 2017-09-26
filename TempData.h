/*
 * TempData.h
 *
 *  Created on: 12-Sep-2017
 *      Author: ubuntu
 */

#ifndef OTFS_SRC_APP_DASHBOARD_TEST_TEMPDATA_H_
#define OTFS_SRC_APP_DASHBOARD_TEST_TEMPDATA_H_
#include "mocker.h"
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

#define CONNECTION_STATUS  0
#define CONNECTION_PII 1
#define VERSION_HW 2
#define VERSION_SW 3
#define CONNECTION_IP 4
#define CONNECTION_SSID 5
#define CONNECTION_ROLE 6
#define BANDWIDTH 7
#define BANDWIDTH_STATUS 8
#define FREQUENCY 9
#define TDDSCHEDULE 10
#define RADIO_ADMIN_MODE 11
#define WIRELESS_RADIO_TX_POWER 12
#define WIRELESS_RADIO_STATUS_TX_POWER 13
#define HUB_STATE 14
#define HUB_RCV_GAIN_LEVEL 15
#define WIRELESS_MODE 16
#define CPE_O_1 17
#define CPE_1_2 18
#define BEAM_ID 19
#define CPE_1_STATE 20
#define CPE_2_STATE 21

class TempData{

private :
	TempData();
	TempData(std::string path);
	static TempData *s_instance;
	static Poco::AutoPtr<Poco::Util::JSONConfiguration> instanceConf(std::string);
//NOTE Wireless True Start
	void getHubWirelessTrue(Poco::JSON::Object &object);
	void getStatusWirelessTrue(Poco::JSON::Object &object);
	void getStatusRStreamsWirelessTrue(Poco::JSON::Array &array);
//NOTE Wireless True End

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
	//blank object
	Poco::JSON::Object blank;

	object.set("chest", blank);
	object.set("cpe", blank);
	object.set("downlink", blank);
	//hub wireless true
	Poco::JSON::Object hub;
	this->getHubWirelessTrue(hub);
	object.set("hub", hub);
	object.set("interference-detection", blank);
	object.set("phy", blank);
	object.set("radio", "");
	object.set("remotes", "");
	Poco::JSON::Object status;
	this->getStatusWirelessTrue(status);
	object.set("status", status);
	object.set("uplink", blank);
}


void TempData::getHubWirelessTrue(Poco::JSON::Object &object){

	Poco::JSON::Object status;
	status.set("channel-profile", 0);
	status.set("rcv-gain-level", 30);
	status.set("schedule", "DD");
	status.set("ssid", "CohereSSID");
	status.set("state", "Unidirectional");
	object.set("status", status);

}

void TempData::getStatusWirelessTrue(Poco::JSON::Object &status){

	status.set("admin-state", "enable");
	status.set("mode", "p2mp");
	status.set("role", "hub");

	Poco::JSON::Array rstreams;
	this->getStatusRStreamsWirelessTrue(rstreams);
	status.set("rstreams", rstreams);//need 2 streams, currently 1

	Poco::JSON::Array streams;
	this->getStatusRStreamsWirelessTrue(streams);
	status.set("streams", streams);

	Poco::JSON::Object throughput;
	throughput.set("L1", 11194);
	throughput.set("L2", 172);
	status.set("throughput", throughput);

	status.set("uptime", "24963");


}

void TempData::getStatusRStreamsWirelessTrue(Poco::JSON::Array &array){
	Poco::JSON::Object object1;
	object1.set("id", 0);
	object1.set("name", "NOEXISTS");

	Poco::JSON::Object obj;
	Poco::JSON::Object ber;
	Poco::JSON::Object codeword;
	codeword.set("correctable", 0);
	codeword.set("uncorrectable", 0);
	codeword.set("total", 0);
	ber.set("codeword", codeword);
	ber.set("total", 0);
	ber.set("last", 0);
	obj.set("ber", ber);
	obj.set("mcs", "QAM4");
	obj.set("resources", 0);
	obj.set("rid", 1);

	Poco::JSON::Object snr;
	snr.set("average", "NOEXISTS");
	snr.set("current", "NOEXISTS");
	snr.set("maximum", "NOEXISTS");
	snr.set("minimum", "NOEXISTS");
	snr.set("variance", "NOEXISTS");
	obj.set("snr", snr);


	Poco::JSON::Object throughput;

	Poco::JSON::Object errors;
	errors.set("frames", "NOEXISTS");
	errors.set("rate", "NOEXISTS");
	throughput.set("errors", errors);

	Poco::JSON::Object rx;
	rx.set("capacity", "NOEXISTS");
	rx.set("frames", "NOEXISTS");
	rx.set("rate", "NOEXISTS");
	throughput.set("rx", "NOEXISTS");

	Poco::JSON::Object tx;
	tx.set("capacity", 5197);
	tx.set("frames", 9484278);
	tx.set("rate", 0);
	throughput.set("tx", "NOEXISTS");

	obj.set("throughput", throughput);

	Poco::JSON::Array remotes;
	remotes.add(obj);
	object1.set("remotes", remotes);
	array.add(object1);
}


#endif /* OTFS_SRC_APP_DASHBOARD_TEST_TEMPDATA_H_ */

