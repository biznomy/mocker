/*
 * wirelessTrue.h
 *
 *  Created on: 26-Sep-2017
 *      Author: ubuntu
 */

#ifndef WIRELESSTRUE_H_
#define WIRELESSTRUE_H_

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

using Poco::Util::JSONConfiguration;


class WirelessTrue{

private :

//NOTE Wireless True Start
	void getHubWirelessTrue(Poco::JSON::Object &object, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf);
	void getStatusWirelessTrue(Poco::JSON::Object &object, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf);
	void getStatusRStreamsWirelessTrue(Poco::JSON::Array &array, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf);
//NOTE Wireless True End

public :
	Poco::DateTime date;
	virtual ~WirelessTrue();
	void generateInteger(Poco::JSON::Object &object, std::string key, int lower, int upper, int fluctuation);
	void generateFloat(Poco::JSON::Object &object, std::string key, float lower, float upper, float fluctuation);
	void generateLong(Poco::JSON::Object &object, std::string key, long lower, long upper, long fluctuation);
	void generateDouble(Poco::JSON::Object &object, std::string key, double lower, double upper, double fluctuation);

	void getWirelessTrue(Poco::JSON::Object &object, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf);
};



WirelessTrue::~WirelessTrue() {
//	cout << "close object WirelessTrue" << endl;
}

/**
 * param [&object : Poco::JSON::Object address]
 * param [key : std:string]
 * param [lower : int -> lowest possible value]
 * param [upper : int -> upper possible value]
 * param [fluctuation : int -> fluctuation (around mean: (lower+upper)/2) possible value]
 * return void
 **/
void WirelessTrue::generateInteger(Poco::JSON::Object &object, std::string key, int lower, int upper, int fluctuation){
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
void WirelessTrue::generateFloat(Poco::JSON::Object &object, std::string key, float lower, float upper, float fluctuation){
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
void WirelessTrue::generateLong(Poco::JSON::Object &object, std::string key, long lower, long upper, long fluctuation){
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
void WirelessTrue::generateDouble(Poco::JSON::Object &object, std::string key, double lower, double upper, double fluctuation){
	object.set(key, Mocker::getRandomMeanDouble(lower, upper, fluctuation));
}

void WirelessTrue::getWirelessTrue(Poco::JSON::Object &object, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf){

	//blank object
	Poco::JSON::Object blank;

	object.set("chest", blank);
	object.set("cpe", blank);
	object.set("downlink", blank);
	//hub wireless true
	Poco::JSON::Object hub;
	this->getHubWirelessTrue(hub, pConf);
	object.set("hub", hub);
	object.set("interference-detection", blank);
	object.set("phy", blank);
	object.set("radio", pConf->getString("wirelessTrue.wireless.radio"));
	object.set("remotes", pConf->getString("wirelessTrue.wireless.remotes"));
	Poco::JSON::Object status;
	this->getStatusWirelessTrue(status, pConf);
	object.set("status", status);
	object.set("uplink", blank);
}


void WirelessTrue::getHubWirelessTrue(Poco::JSON::Object &object, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf){

	Poco::JSON::Object status;
	status.set("channel-profile", pConf->getString("wirelessTrue.wireless.hub.status.channel-profile"));
	status.set("rcv-gain-level", pConf->getString("wirelessTrue.wireless.hub.status.rcv-gain-level"));
	status.set("schedule", pConf->getString("wirelessTrue.wireless.hub.status.schedule"));
	status.set("ssid", pConf->getString("wirelessTrue.wireless.hub.status.ssid"));
	status.set("state", pConf->getString("wirelessTrue.wireless.hub.status.state"));
	object.set("status", status);

}

void WirelessTrue::getStatusWirelessTrue(Poco::JSON::Object &status, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf){

	status.set("admin-state", pConf->getString("wirelessTrue.wireless.status.admin-state"));
	status.set("mode", pConf->getString("wirelessTrue.wireless.status.mode"));
	status.set("role", pConf->getString("wirelessTrue.wireless.status.role"));

	Poco::JSON::Array rstreams;
	this->getStatusRStreamsWirelessTrue(rstreams, pConf);
	status.set("rstreams", rstreams);//need 2 streams, currently 1

	Poco::JSON::Array streams;
	this->getStatusRStreamsWirelessTrue(streams, pConf);
	status.set("streams", streams);

	Poco::JSON::Object throughput;
	throughput.set("L1", pConf->getString("wirelessTrue.wireless.status.throughput.L1"));
	throughput.set("L2", pConf->getString("wirelessTrue.wireless.status.throughput.L2"));
	status.set("throughput", throughput);

	status.set("uptime", pConf->getString("wirelessTrue.wireless.status.uptime"));


}

void WirelessTrue::getStatusRStreamsWirelessTrue(Poco::JSON::Array &array, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf){

//	cout <<  "streams" << pConf->getString("wirelessTrue.wireless.status.rstreams") << endl;



	Poco::JSON::Object object;

	object.set("id", 0);
	object.set("name", "NOEXISTS");

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
	throughput.set("rx", rx);

	Poco::JSON::Object tx;
	tx.set("capacity", 5197);
	tx.set("frames", 9484278);
	tx.set("rate", 0);
	throughput.set("tx", tx);

	obj.set("throughput", throughput);

	Poco::JSON::Array remotes;
	remotes.add(obj);
	object.set("remotes", remotes);
	array.add(object);
}




#endif /* WIRELESSTRUE_H_ */
