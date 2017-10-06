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


long true_time_value;
int k=0;
class WirelessTrue{

private :

//NOTE Wireless True Start
	void getHubWirelessTrue(Poco::JSON::Object &object, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf);
	void getRadioWirelessTrue(Poco::JSON::Object &object, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf);
	void getRemoteWirelessTrue(Poco::JSON::Array &array, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf);
	void getRemoteStreamsWirelessTrue(Poco::JSON::Array& streams, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf, const int i, const int max);
	void getStatusWirelessTrue(Poco::JSON::Object &object, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf);
	void getStatusRStreamsWirelessTrue(Poco::JSON::Array &array, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf);
	void generateBer(Poco::JSON::Object &object, std::string key, int decimalPlaces, double lower, double upper, double fluctuation);
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
	Poco::Timestamp thisnow;
	true_time_value = thisnow.epochTime();
	if(k < 60){k++;}else{k=0;}
}

/**
 * generate ber(bit error rate)
 * param [&object : Poco::JSON::Object address]
 * param [key : std:string]
 * param [decimalPlaces : int] //for getting stable exponential value
 * param [lower : double -> lowest possible value]
 * param [upper : double -> upper possible value]
 * param [fluctuation : double -> fluctuation (around mean: (lower+upper)/2) possible value]
 * return void
 **/
void WirelessTrue::generateBer(Poco::JSON::Object& object, std::string key, int decimalPlaces, double lower, double upper, double fluctuation) {
	double number = Mocker::getRandomMeanDouble(lower, upper, fluctuation);
	object.set(key, Poco::format("%0.1E", number/pow10(decimalPlaces)));
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
	Poco::JSON::Object radio;
	this->getRadioWirelessTrue(radio, pConf);
	object.set("radio", radio);
	Poco::JSON::Array remote;
	this->getRemoteWirelessTrue(remote, pConf);
	object.set("remotes", remote);
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
	status.set("state", pConf->getString(Poco::format("wirelessTrue.wireless.hub.status.state.[%d]", k)));

	object.set("status", status);

}

void WirelessTrue::getRadioWirelessTrue(Poco::JSON::Object &object, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf){

	Poco::JSON::Object blank;
	object.set("admin-mode", pConf->getString("wirelessTrue.wireless.radio.admin-mode"));

	Poco::JSON::Array antenna;
	Poco::JSON::Object antennaObj;

	antennaObj.set("antennaID", pConf->getString("wirelessTrue.wireless.radio.antenna.antennaID"));
	antennaObj.set("rx-gain", pConf->getString("wirelessTrue.wireless.radio.antenna.rx-gain"));
	antennaObj.set("status", blank);
	antennaObj.set("tx-attenuation", pConf->getString("wirelessTrue.wireless.radio.antenna.tx-attenuation"));
	antenna.add(antennaObj);
	object.set("antenna", antenna);

	object.set("automatic-gain", pConf->getString("wirelessTrue.wireless.radio.automatic-gain"));
	object.set("bandwidth", pConf->getString("wirelessTrue.wireless.radio.bandwidth"));
	object.set("beam-id", pConf->getString("wirelessTrue.wireless.radio.beam-id"));
	object.set("frequency", pConf->getString("wirelessTrue.wireless.radio.frequency"));
	object.set("link-distance", pConf->getString("wirelessTrue.wireless.radio.link-distance"));

	Poco::JSON::Object status;
//	cout << pConf->getString("wirelessTrue.wireless.radio.status") << endl;
	status.set("bandwidth", pConf->getString("wirelessTrue.wireless.radio.status.bandwidth"));
	status.set("frequency", pConf->getString("wirelessTrue.wireless.radio.status.frequency"));
	status.set("align-level", pConf->getString("wirelessTrue.wireless.radio.status.align-level"));
	status.set("tx-power", pConf->getString("wirelessTrue.wireless.radio.status.tx-power"));
	object.set("status", status);

	object.set("sto", pConf->getString("wirelessTrue.wireless.radio.sto"));
	object.set("target-rssi", pConf->getString("wirelessTrue.wireless.radio.target-rssi"));
	object.set("tx-power", pConf->getString("wirelessTrue.wireless.radio.tx-power"));
	object.set("txSwap", pConf->getString("wirelessTrue.wireless.radio.txSwap"));
}
void WirelessTrue::getRemoteWirelessTrue(Poco::JSON::Array &array, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf){
	Poco::JSON::Object blank;
	Poco::JSON::Object remote;

	int i = pConf->getInt("wirelessFalse.wireless.remotes.remotes-start");
	int max = pConf->getInt("wirelessFalse.wireless.remotes.remotes-end");

	for( ; i <= max ; i++ ){

			remote.set("admin-state", pConf->getString("wirelessFalse.wireless.remotes.admin-state"));

			Poco::JSON::Object downlink;
			Poco::JSON::Array downlink_streams;
			this->getRemoteStreamsWirelessTrue(downlink_streams, pConf, i, max);
			downlink.set("streams", downlink_streams);
			remote.set("downlink", downlink);

			remote.set("id", Poco::format("%d", i));
			remote.set("name", Poco::format("name-%d", i));

			Poco::JSON::Object status;
			status.set("throughput", blank);
			status.set("state", "Connected");
			remote.set("status", status);

			Poco::JSON::Object uplink;
			Poco::JSON::Object override;
			override.set("power", pConf->getString("wirelessFalse.wireless.remotes.uplink.override.power"));
			override.set("timing", pConf->getString("wirelessFalse.wireless.remotes.uplink.override.timing"));
			uplink.set("override", override);

			Poco::JSON::Array streams;
			this->getRemoteStreamsWirelessTrue(streams, pConf, i, max);
			uplink.set("streams", streams);

			remote.set("uplink", uplink);

			array.add(remote);
	}
}

void WirelessTrue::getRemoteStreamsWirelessTrue(Poco::JSON::Array& streams, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf, const int i, const int max) {
	Poco::JSON::Object stream;
	stream.set("id", Poco::format("%d", i));
	stream.set("mcs", pConf->getString("wirelessFalse.wireless.remotes.downlink.streams.mcs"));
	stream.set("weight", (pConf->getInt("wirelessFalse.wireless.remotes.downlink.streams.weight")/max));
	streams.add(stream);
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
	generateLong(throughput, "L1", Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.throughput.L1.lower")), Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.throughput.L1.upper")), Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.throughput.L1.flactuation")));
	generateLong(throughput, "L2", Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.throughput.L2.lower")), Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.throughput.L2.upper")), Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.throughput.L2.flactuation")));
	status.set("throughput", throughput);

	//TODO up - time
	status.set("uptime", (true_time_value - static_time_value));


}

void WirelessTrue::getStatusRStreamsWirelessTrue(Poco::JSON::Array &array, Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf){

	int max = pConf->getInt("wirelessTrue.wireless.status.rstreams.streams-end");
	int i = pConf->getInt("wirelessTrue.wireless.status.rstreams.streams-start");;
	for( ;i <= max ;i++){

			Poco::JSON::Object object;
			object.set("id", Poco::format("%d", i));
			object.set("name", Poco::format("name-%d", i));

			Poco::JSON::Object obj;

			Poco::JSON::Object ber;
			Poco::JSON::Object codeword;
			generateFloat(codeword, "correctable", Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber.codeword.correctable.lower")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber.codeword.correctable.upper")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber.codeword.correctable.flactuation")));
			generateFloat(codeword, "uncorrectable", Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber.codeword.uncorrectable.lower")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber.codeword.uncorrectable.upper")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber.codeword.uncorrectable.flactuation")));
			generateFloat(codeword, "total", Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber.codeword.total.lower")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber.codeword.total.upper")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber.codeword.total.flactuation")));
			ber.set("codeword", codeword);
			generateBer(ber, "total", 4, Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber.total.lower")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber.total.upper")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber.total.flactuation")));
			generateBer(ber, "last", 4, Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber.last.lower")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber.last.upper")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber.last.flactuation")));
			obj.set("ber", ber);

			Poco::JSON::Object ber_dl;
			Poco::JSON::Object codeword_dl;
			generateFloat(codeword_dl, "correctable", Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber-dl.codeword.correctable.lower")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber-dl.codeword.correctable.upper")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber-dl.codeword.correctable.flactuation")));
			generateFloat(codeword_dl, "uncorrectable", Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber-dl.codeword.uncorrectable.lower")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber-dl.codeword.uncorrectable.upper")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber-dl.codeword.uncorrectable.flactuation")));
			generateFloat(codeword_dl, "total", Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber-dl.codeword.total.lower")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber-dl.codeword.total.upper")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber-dl.codeword.total.flactuation")));
			ber_dl.set("codeword", codeword_dl);
			generateBer(ber_dl, "total", 4, Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber-dl.total.lower")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber-dl.total.upper")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber-dl.total.flactuation")));
			generateBer(ber_dl, "last", 4, Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber-dl.last.lower")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber-dl.last.upper")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.ber-dl.last.flactuation")));
			obj.set("ber-dl", ber_dl);



			obj.set("mcs", pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.mcs"));
			obj.set("resources", pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.resources"));

			obj.set("rid", pConf->getInt("wirelessTrue.wireless.status.rstreams.remotes.rid") + i);

			Poco::JSON::Object snr;
			generateFloat(snr, "average", Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr.average.lower")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr.average.upper")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr.average.flactuation")));
			generateFloat(snr, "current", Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr.current.lower")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr.current.upper")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr.current.flactuation")));
			generateFloat(snr, "maximum", Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr.maximum.lower")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr.maximum.upper")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr.maximum.flactuation")));
			generateFloat(snr, "minimum", Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr.minimum.lower")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr.minimum.upper")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr.minimum.flactuation")));
			generateFloat(snr, "variance", Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr.variance.lower")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr.variance.upper")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr.variance.flactuation")));
			obj.set("snr", snr);

			Poco::JSON::Object snr_dl;
			generateFloat(snr_dl, "average", Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr.average.lower")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr.average.upper")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr-dl.average.flactuation")));
			generateFloat(snr_dl, "current", Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr.current.lower")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr.current.upper")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr-dl.current.flactuation")));
			generateFloat(snr_dl, "maximum", Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr.maximum.lower")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr.maximum.upper")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr-dl.maximum.flactuation")));
			generateFloat(snr_dl, "minimum", Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr.minimum.lower")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr.minimum.upper")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr-dl.minimum.flactuation")));
			generateFloat(snr_dl, "variance", Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr.variance.lower")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr.variance.upper")), Mocker::getFloat(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.snr-dl.variance.flactuation")));
			obj.set("snr-dl", snr_dl);


			Poco::JSON::Object throughput;

			Poco::JSON::Object errors;
			generateLong(errors, "frames", Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.throughput.errors.frames.lower")), Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.throughput.errors.frames.upper")), Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.throughput.errors.frames.flactuation")));
			generateLong(errors, "rate", Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.throughput.errors.rate.lower")), Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.throughput.errors.rate.upper")), Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.throughput.errors.rate.flactuation")));
			throughput.set("errors", errors);

			Poco::JSON::Object rx;
			generateLong(rx, "capacity", Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.throughput.rx.capacity.lower")), Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.throughput.rx.capacity.upper")), Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.throughput.rx.capacity.flactuation")));
			generateLong(rx, "frames", Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.throughput.rx.frames.lower")), Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.throughput.rx.frames.upper")), Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.throughput.rx.frames.flactuation")));
			generateLong(rx, "rate", Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.throughput.rx.rate.lower")), Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.throughput.rx.rate.upper")), Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.throughput.rx.rate.flactuation")));
			throughput.set("rx", rx);

			Poco::JSON::Object tx;
			generateLong(tx, "capacity", Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.throughput.tx.capacity.lower")), Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.throughput.tx.capacity.upper")), Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.throughput.tx.capacity.flactuation")));
			generateLong(tx, "frames", Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.throughput.tx.frames.lower")), Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.throughput.tx.frames.upper")), Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.throughput.tx.frames.flactuation")));
			generateLong(tx, "rate", Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.throughput.tx.rate.lower")), Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.throughput.tx.rate.upper")), Mocker::getLong(pConf->getString("wirelessTrue.wireless.status.rstreams.remotes.throughput.tx.rate.flactuation")));
			throughput.set("tx", tx);

			obj.set("throughput", throughput);

			Poco::JSON::Array remotes;
			remotes.add(obj);
			object.set("remotes", remotes);
			array.add(object);

	}


}




#endif /* WIRELESSTRUE_H_ */
