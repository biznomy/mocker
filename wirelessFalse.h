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
	void getChestWirelessFalse(Poco::JSON::Object &object, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf);
	void getCpeWirelessFalse(Poco::JSON::Object &object, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf);
	void getHubWirelessFalse(Poco::JSON::Object &object, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf);
	void getInterferenceDetectionWirelessFalse(Poco::JSON::Object &object, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf);
	void getPhyWirelessFalse(Poco::JSON::Object &object, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf);
	void getRadioWirelessFalse(Poco::JSON::Object &object, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf);
	void getRemoteWirelessFalse(Poco::JSON::Array &array, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf);
	void getRemoteStreamsWirelessFalse(Poco::JSON::Array& streams, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf, const int i);
	void getStatusWirelessFalse(Poco::JSON::Object &object, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf);
	void getStatusRStreamsWirelessFalse(Poco::JSON::Array &array, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf);

//NOTE Wireless False End

public :
	Poco::DateTime date;
	virtual ~WirelessFalse();
	void generateInteger(Poco::JSON::Object &object, std::string key, int lower, int upper, int fluctuation);
	void generateFloat(Poco::JSON::Object &object, std::string key, float lower, float upper, float fluctuation);
	void generateLong(Poco::JSON::Object &object, std::string key, long lower, long upper, long fluctuation);
	void generateDouble(Poco::JSON::Object &object, std::string key, double lower, double upper, double fluctuation);

	void getWirelessFalse(Poco::JSON::Object &object, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf);
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



void WirelessFalse::getWirelessFalse(Poco::JSON::Object &object, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf){

	//blank object
	Poco::JSON::Object blank;
	object.set("admin-state", pConf->getString("wirelessFalse.wireless.admin-state"));

	Poco::JSON::Object chest;
	this->getChestWirelessFalse(chest, pConf);
	object.set("chest", chest);

	Poco::JSON::Object cpe;
	this->getCpeWirelessFalse(cpe, pConf);
	object.set("cpe", cpe);
	object.set("downlink", blank);

	Poco::JSON::Object hub;
	this->getHubWirelessFalse(hub, pConf);
	object.set("hub", hub);

	Poco::JSON::Object interference_detection;
	this->getInterferenceDetectionWirelessFalse(interference_detection, pConf);
	object.set("interference-detection", interference_detection);

	object.set("mode", pConf->getString("wirelessFalse.wireless.mode"));


	Poco::JSON::Object phy;
	this->getPhyWirelessFalse(phy, pConf);
	object.set("phy", phy);

	Poco::JSON::Object radio;
	this->getRadioWirelessFalse(radio, pConf);
	object.set("radio", radio);

	Poco::JSON::Array remotes;
	this->getRemoteWirelessFalse(remotes, pConf);
	object.set("remotes", remotes);

	Poco::JSON::Object status;
	this->getStatusWirelessFalse(status, pConf);
	object.set("status", status);

	object.set("uplink", blank);
}


void WirelessFalse::getChestWirelessFalse(Poco::JSON::Object &object, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf){
	object.set("dfe-disable", pConf->getString("wirelessFalse.wireless.chest.dfe-disable"));
	object.set("dfe-len", pConf->getString("wirelessFalse.wireless.chest.dfe-len"));
	object.set("doppler-bw", pConf->getString("wirelessFalse.wireless.chest.doppler-bw"));
}

void WirelessFalse::getCpeWirelessFalse(Poco::JSON::Object &object, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf){
	object.set("id", pConf->getString("wirelessFalse.wireless.cpe.id"));
}

void WirelessFalse::getHubWirelessFalse(Poco::JSON::Object &object, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf){
	Poco::JSON::Object blank;
	object.set("name", pConf->getString("wirelessFalse.wireless.hub.name"));
	object.set("channel-profile", pConf->getString("wirelessFalse.wireless.hub.channel-profile"));
	object.set("rcv-gain-level", pConf->getString("wirelessFalse.wireless.hub.rcv-gain-level"));
	object.set("schedule", pConf->getString("wirelessFalse.wireless.hub.schedule"));
	object.set("ssid", pConf->getString("wirelessFalse.wireless.hub.ssid"));
	object.set("status", blank);
}


void WirelessFalse::getInterferenceDetectionWirelessFalse(Poco::JSON::Object &object, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf){

	object.set("admin-mode", pConf->getString("wirelessFalse.wireless.interference-detection.admin-mode"));
	object.set("threshold", pConf->getString("wirelessFalse.wireless.interference-detection.threshold"));
}

void WirelessFalse::getPhyWirelessFalse(Poco::JSON::Object &object, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf){
	object.set("channel-post", pConf->getString("wirelessFalse.wireless.phy.channel-post"));
	object.set("channel-pre", pConf->getString("wirelessFalse.wireless.phy.channel-pre"));
	object.set("cyclic-postfix", pConf->getString("wirelessFalse.wireless.phy.cyclic-postfix"));
	object.set("cyclic-prefix", pConf->getString("wirelessFalse.wireless.phy.cyclic-prefix"));
}

void WirelessFalse::getRadioWirelessFalse(Poco::JSON::Object &object, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf){

	Poco::JSON::Object blank;
	object.set("admin-mode", pConf->getString("wirelessFalse.wireless.radio.admin-mode"));

	Poco::JSON::Array antenna;
	Poco::JSON::Object antennaObj;

	antennaObj.set("antennaID", pConf->getString("wirelessFalse.wireless.radio.antenna.antennaID"));
	antennaObj.set("rx-gain", pConf->getString("wirelessFalse.wireless.radio.antenna.rx-gain"));
	antennaObj.set("status", blank);
	antennaObj.set("tx-attenuation", pConf->getString("wirelessFalse.wireless.radio.antenna.tx-attenuation"));
	antenna.add(antennaObj);
	object.set("antenna", antenna);

	object.set("automatic-gain", pConf->getString("wirelessFalse.wireless.radio.automatic-gain"));
	object.set("bandwidth", pConf->getString("wirelessFalse.wireless.radio.bandwidth"));
	object.set("beam-id", pConf->getString("wirelessFalse.wireless.radio.beam-id"));
	object.set("frequency", pConf->getString("wirelessFalse.wireless.radio.frequency"));
	object.set("link-distance", pConf->getString("wirelessFalse.wireless.radio.link-distance"));

//	Poco::JSON::Object status;
//	status.set("bandwidth", pConf->getString("wirelessFalse.wireless.radio.bandwidth"));//TODO CHANGE
//	status.set("frequency", pConf->getString("wirelessFalse.wireless.radio.frequency"));//TODO CHANGE
//	status.set("align-level", "");//TODO CHANGE
//	status.set("tx-power", 0);//TODO CHANGE

	object.set("status", blank);
	object.set("sto", pConf->getString("wirelessFalse.wireless.radio.sto"));
	object.set("target-rssi", pConf->getString("wirelessFalse.wireless.radio.target-rssi"));
	object.set("tx-power", pConf->getString("wirelessFalse.wireless.radio.tx-power"));
	object.set("txSwap", pConf->getString("wirelessFalse.wireless.radio.txSwap"));

}

void WirelessFalse::getRemoteWirelessFalse(Poco::JSON::Array &array, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf){
	Poco::JSON::Object blank;
	Poco::JSON::Object remote;

	int i = pConf->getInt("wirelessFalse.wireless.remotes.remotes-start");
	int max = pConf->getInt("wirelessFalse.wireless.remotes.remotes-end");

	for( ; i <= max ; i++ ){

			remote.set("admin-state", pConf->getString("wirelessFalse.wireless.remotes.admin-state"));

			Poco::JSON::Object downlink;
			Poco::JSON::Array downlink_streams;
			this->getRemoteStreamsWirelessFalse(downlink_streams, pConf, i);
			downlink.set("streams", downlink_streams);
			remote.set("downlink", downlink);

			remote.set("id", Poco::format("%d", i));
			remote.set("name", Poco::format("name-%d", i));

			Poco::JSON::Object status;
			status.set("throughput", blank);
			status.set("mac-address", pConf->getString("wirelessFalse.wireless.remotes.status.mac-address"));
			status.set("uptime", pConf->getString("wirelessFalse.wireless.remotes.status.uptime"));
			status.set("state", "Connected");
			remote.set("status", status);

			Poco::JSON::Object uplink;
			Poco::JSON::Object override;
			override.set("power", pConf->getString("wirelessFalse.wireless.remotes.uplink.override.power"));
			override.set("timing", pConf->getString("wirelessFalse.wireless.remotes.uplink.override.timing"));
			uplink.set("override", override);

			Poco::JSON::Array streams;
			this->getRemoteStreamsWirelessFalse(streams, pConf, i);
			uplink.set("streams", streams);

			remote.set("uplink", uplink);

			array.add(remote);
	}
}


void WirelessFalse::getRemoteStreamsWirelessFalse(Poco::JSON::Array& streams, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf, const int i) {
	Poco::JSON::Object stream;
	stream.set("id", Poco::format("%d", i));
	stream.set("mcs", pConf->getString("wirelessFalse.wireless.remotes.downlink.streams.mcs"));
	stream.set("weight", pConf->getString("wirelessFalse.wireless.remotes.downlink.streams.weight"));
	streams.add(stream);
}

void WirelessFalse::getStatusWirelessFalse(Poco::JSON::Object &status, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf){

	Poco::JSON::Object blank;

//	pConf->getString("wirelessFalse.wireless.status")
	Poco::JSON::Array rstreams;
	this->getStatusRStreamsWirelessFalse(rstreams, pConf);
	status.set("rstreams", rstreams);

	Poco::JSON::Array streams;
	this->getStatusRStreamsWirelessFalse(streams, pConf);
	status.set("streams", streams);

	status.set("throughput", blank);

}

void WirelessFalse::getStatusRStreamsWirelessFalse(Poco::JSON::Array &array, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf){
	Poco::JSON::Object object;
	object.set("id", pConf->getString("wirelessFalse.wireless.status.rstreams.id"));

	Poco::JSON::Object blank;

	Poco::JSON::Object obj;
	Poco::JSON::Object ber;
	ber.set("codeword", blank);
	obj.set("ber", blank);
	obj.set("rid", pConf->getString("wirelessFalse.wireless.status.rstreams.remotes.rid"));
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
