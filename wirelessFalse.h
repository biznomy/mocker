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

long false_time_value;
static Poco::JSON::Array constStreams;
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
	void getRemoteStreamsWirelessFalse(Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf, const int i, const int max, const int streamC);
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
	Poco::Timestamp thisnow;
	false_time_value = thisnow.epochTime();
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
	int streamC = pConf->getInt("wirelessFalse.wireless.remotes.remotes-stream-count");


	for( ; i <= max ; i++ ){

			remote.set("admin-state", pConf->getString("wirelessFalse.wireless.remotes.admin-state"));

			Poco::JSON::Object downlink;

			this->getRemoteStreamsWirelessFalse(pConf, i, max, streamC);
			downlink.set("streams", constStreams);

			remote.set("downlink", downlink);

			remote.set("id", Poco::format("%d", i));
			remote.set("name", Poco::format("SJC-%0003d", i));

			Poco::JSON::Object status;
			status.set("throughput", blank);
			remote.set("status", status);

			Poco::JSON::Object uplink;
			Poco::JSON::Object override;
			override.set("power", pConf->getString("wirelessFalse.wireless.remotes.uplink.override.power"));
			override.set("timing", pConf->getString("wirelessFalse.wireless.remotes.uplink.override.timing"));
			uplink.set("override", override);

			this->getRemoteStreamsWirelessFalse(pConf, i, max, streamC);
			uplink.set("streams", constStreams);

			remote.set("uplink", uplink);

			array.add(remote);
	}
}


void WirelessFalse::getRemoteStreamsWirelessFalse(Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf, const int i, const int max, const int streamC) {
	if(constStreams.size()==4){
		return;
	}
	int variable = i-1;
	for(;variable < streamC; ++variable){
		Poco::JSON::Object stream;
		stream.set("id", Poco::format("%d", variable));
		std::string fetchQAM = Poco::format("wirelessFalse.wireless.remotes.downlink.streams.mcs[%d]", variable);
		stream.set("mcs", pConf->getString(fetchQAM));
		int weight = pConf->getInt("wirelessFalse.wireless.remotes.downlink.streams.weight")/max;
		stream.set("weight", Poco::format("%d", getRandom(weight - 5, weight + 5)));
		constStreams.add(stream);
	}
}

void WirelessFalse::getStatusWirelessFalse(Poco::JSON::Object &status, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf){

	Poco::JSON::Object blank;
	Poco::JSON::Array rstreams;
	this->getStatusRStreamsWirelessFalse(rstreams, pConf);
	status.set("rstreams", rstreams);

	Poco::JSON::Array streams;
	this->getStatusRStreamsWirelessFalse(streams, pConf);
	status.set("streams", streams);

	status.set("throughput", blank);

}

void WirelessFalse::getStatusRStreamsWirelessFalse(Poco::JSON::Array &array, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf){

	//This 2 dimensional array represents mapping of cpe and streams
	// currently this has 4 streams ...
	int c[10][10] = {
			{1,2,3,4,6,7,8,9,10,0},
			{1,2,4,6,7,8,0,0,0,0},
			{1,4,6,8,9,0,0,0,0,0},
			{1,5,6,8,10,0,0,0,0,0}
	};

	int x = 0;
	int z = 0;
	for(; x < 4; ++x){
		Poco::JSON::Array remotes;
		for(;z < 10; ++z){
			if(c[x][z] == 0){
				break;
			}

			Poco::JSON::Object obj;
			Poco::JSON::Object blank;

			Poco::JSON::Object ber;
			ber.set("codeword", blank);
			obj.set("ber", ber);

			Poco::JSON::Object ber_dl;
			ber_dl.set("codeword", blank);
			obj.set("ber-dl", ber_dl);

			obj.set("rid", Poco::format("%d", c[x][z]));

			obj.set("snr", blank);
			obj.set("snr-dl", blank);


			Poco::JSON::Object throughput;
			throughput.set("errors", blank);
			throughput.set("rx", blank);
			throughput.set("tx", blank);

			obj.set("throughput", throughput);
			remotes.add(obj);

		}
		z=0;

		Poco::JSON::Object object;
		object.set("id", Poco::format("%d", x));
		object.set("remotes", remotes);

		array.add(object);
	}
}




#endif /* WIRELESSFALSE_H_ */
