/*
 * wirelessFalse.h
 *
 *  Created on: 26-Sep-2017
 *      Author: ubuntu
 */

#ifndef WIRELESSFALSE_H_
#define WIRELESSFALSE_H_

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


class WirelessFalse{

private :
//NOTE Wireless False Start
	void getChestWirelessFalse(Poco::JSON::Object &object);
	void getCpeWirelessFalse(Poco::JSON::Object &object);
	void getHubWirelessFalse(Poco::JSON::Object &object);
	void getInterferenceDetectionWirelessFalse(Poco::JSON::Object &object);
	void getPhyWirelessFalse(Poco::JSON::Object &object);
	void getRadioWirelessFalse(Poco::JSON::Object &object);
	void getRemoteWirelessFalse(Poco::JSON::Array &array);
	void getRemoteStreamsWirelessFalse(Poco::JSON::Array& streams);
	void getStatusWirelessFalse(Poco::JSON::Object &object);
	void getStatusRStreamsWirelessFalse(Poco::JSON::Array &array);

//NOTE Wireless False End

public :
	Poco::DateTime date;
	virtual ~WirelessFalse();
	void generateInteger(Poco::JSON::Object &object, std::string key, int lower, int upper, int fluctuation);
	void generateFloat(Poco::JSON::Object &object, std::string key, float lower, float upper, float fluctuation);
	void generateLong(Poco::JSON::Object &object, std::string key, long lower, long upper, long fluctuation);
	void generateDouble(Poco::JSON::Object &object, std::string key, double lower, double upper, double fluctuation);

	void getWirelessFalse(Poco::JSON::Object &object);
};



WirelessFalse::~WirelessFalse() {
//	cout << "close object WirelessFalse" << endl;
}

/**
 * param [&object : Poco::JSON::Object address]
 * param [key : std:string]
 * param [lower : int -> lowest possible value]
 * param [upper : int -> upper possible value]
 * param [fluctuation : int -> fluctuation (around mean: (lower+upper)/2) possible value]
 * return void
 **/
void WirelessFalse::generateInteger(Poco::JSON::Object &object, std::string key, int lower, int upper, int fluctuation){
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
void WirelessFalse::generateFloat(Poco::JSON::Object &object, std::string key, float lower, float upper, float fluctuation){
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
void WirelessFalse::generateLong(Poco::JSON::Object &object, std::string key, long lower, long upper, long fluctuation){
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
void WirelessFalse::generateDouble(Poco::JSON::Object &object, std::string key, double lower, double upper, double fluctuation){
	object.set(key, Mocker::getRandomMeanDouble(lower, upper, fluctuation));
}



void WirelessFalse::getWirelessFalse(Poco::JSON::Object &object){
	//blank object
	Poco::JSON::Object blank;

	object.set("admin-state", "enable");

	Poco::JSON::Object chest;
	this->getChestWirelessFalse(chest);
	object.set("chest", chest);

	Poco::JSON::Object cpe;
	this->getCpeWirelessFalse(cpe);
	object.set("cpe", cpe);
	object.set("downlink", blank);

	Poco::JSON::Object hub;
	this->getHubWirelessFalse(hub);
	object.set("hub", hub);

	Poco::JSON::Object interference_detection;
	this->getInterferenceDetectionWirelessFalse(interference_detection);
	object.set("interference-detection", interference_detection);

	object.set("mode", "p2mp");

	Poco::JSON::Object phy;
	this->getPhyWirelessFalse(phy);
	object.set("phy", phy);

	Poco::JSON::Object radio;
	this->getRadioWirelessFalse(radio);
	object.set("radio", radio);

	Poco::JSON::Array remotes;
	this->getRemoteWirelessFalse(remotes);
	object.set("remotes", remotes);


	Poco::JSON::Object status;
	this->getStatusWirelessFalse(status);
	object.set("status", status);

	object.set("uplink", blank);
}


void WirelessFalse::getChestWirelessFalse(Poco::JSON::Object &object){
	object.set("dfe-disable", "NOEXISTS");
	object.set("dfe-len", "31");
	object.set("doppler-bw", "400");
}

void WirelessFalse::getCpeWirelessFalse(Poco::JSON::Object &object){
	object.set("id", "1");
}

void WirelessFalse::getHubWirelessFalse(Poco::JSON::Object &object){
	Poco::JSON::Object blank;
	object.set("name", "CohereHub");
	object.set("channel-profile", 0);
	object.set("rcv-gain-level", 26);
	object.set("schedule", "DL-Only");
	object.set("ssid", "CohereSSID");
	object.set("status", blank);
}


void WirelessFalse::getInterferenceDetectionWirelessFalse(Poco::JSON::Object &object){
	object.set("admin-mode", "disable");
	object.set("threshold", "-70");
}

void WirelessFalse::getPhyWirelessFalse(Poco::JSON::Object &object){
	object.set("channel-post", "103");
	object.set("channel-pre", "24");
	object.set("cyclic-postfix", "24");
	object.set("cyclic-prefix", "40");
}

void WirelessFalse::getRadioWirelessFalse(Poco::JSON::Object &object){

	Poco::JSON::Object blank;
	object.set("admin-mode", "disable");

	Poco::JSON::Array antenna;
	Poco::JSON::Object antennaObj;

	antennaObj.set("antennaID", "0");
	antennaObj.set("rx-gain", "30.0");
	antennaObj.set("status", blank);
	antennaObj.set("tx-attenuation", "15000.0");
	antenna.add(antennaObj);
	object.set("antenna", antenna);

	object.set("automatic-gain", "on");
	object.set("bandwidth", "10MHz");
	object.set("beam-id", "0");
	object.set("frequency", "3612.0");
	object.set("link-distance", "5000");
	object.set("status", blank);
	object.set("sto", "on");
	object.set("target-rssi", "25");
	object.set("tx-power", "NOEXISTS");
	object.set("txSwap", "true");

}

void WirelessFalse::getRemoteStreamsWirelessFalse(Poco::JSON::Array& streams) {
	Poco::JSON::Object stream;
	stream.set("id", "1");
	stream.set("mcs", "QAM4");
	stream.set("weight", "10");
	streams.add(stream);
}

void WirelessFalse::getRemoteWirelessFalse(Poco::JSON::Array &array){
	Poco::JSON::Object blank;
	Poco::JSON::Object remote;

	remote.set("admin-state", "enable");


	Poco::JSON::Object downlink;
	Poco::JSON::Array downlink_streams;
	this->getRemoteStreamsWirelessFalse(downlink_streams);
	downlink.set("streams", downlink_streams);
	remote.set("downlink", downlink);

	remote.set("id", 1);
	remote.set("name", "NOEXISTS");

	Poco::JSON::Object status;
	status.set("throughput", blank);
	remote.set("status", status);

	Poco::JSON::Object uplink;
	Poco::JSON::Object override;
	override.set("power", "NOEXISTS");
	override.set("timing", "NOEXISTS");
	uplink.set("override", override);

	Poco::JSON::Array streams;
	this->getRemoteStreamsWirelessFalse(streams);
	uplink.set("streams", streams);

	remote.set("uplink", uplink);

	array.add(remote);

}

void WirelessFalse::getStatusWirelessFalse(Poco::JSON::Object &status){

	Poco::JSON::Object blank;

	Poco::JSON::Array rstreams;
	this->getStatusRStreamsWirelessFalse(rstreams);
	status.set("rstreams", rstreams);

	Poco::JSON::Array streams;
	this->getStatusRStreamsWirelessFalse(streams);
	status.set("streams", streams);

	status.set("throughput", blank);

}

void WirelessFalse::getStatusRStreamsWirelessFalse(Poco::JSON::Array &array){
	Poco::JSON::Object object;
	object.set("id", 0);

	Poco::JSON::Object blank;

	Poco::JSON::Object obj;
	Poco::JSON::Object ber;
	ber.set("codeword", blank);
	obj.set("ber", blank);
	obj.set("rid", 1);
	obj.set("snr", blank);

	Poco::JSON::Object throughput;
	throughput.set("errors", blank);
	throughput.set("rx", blank);
	throughput.set("tx", blank);
	obj.set("throughput", throughput);

	Poco::JSON::Array remotes;
	remotes.add(obj);
	object.set("remotes", remotes);

	array.add(object);
}




#endif /* WIRELESSFALSE_H_ */
