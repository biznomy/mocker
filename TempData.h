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
#define THR_MAX_CAPI 22
#define THR_BEAM_CAP 23

class TempData{

private :
	TempData();
	TempData(std::string path);
	static TempData *s_instance;
	static Poco::AutoPtr<Poco::Util::JSONConfiguration> instanceConf(std::string);
	void generateSnr(Poco::JSON::Object &object, std::string key, float lower, float upper, float fluctuation);
	void generateBer(Poco::JSON::Object &object, std::string key, int decimalPlaces, double lower, double upper, double fluctuation);
	void generateRssi(Poco::JSON::Object &object, std::string key, int lower, int upper, int fluctuation);
	void generateThroughput(Poco::JSON::Object &object, std::string key, long lower, long upper, long fluctuation);
	void generateCorrectable(Poco::JSON::Object &object, std::string key, float lower, float upper, float fluctuation);

public :
	Poco::DateTime date;
	virtual ~TempData();
	static TempData *instance();
	Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf ;
	void generateInteger(Poco::JSON::Object &object, std::string key, int lower, int upper, int fluctuation);
	void generateFloat(Poco::JSON::Object &object, std::string key, float lower, float upper, float fluctuation);
	void generateLong(Poco::JSON::Object &object, std::string key, long lower, long upper, long fluctuation);
	void generateDouble(Poco::JSON::Object &object, std::string key, double lower, double upper, double fluctuation);
	//
	void generateStaticData(Poco::JSON::Object &object, int choice);
	void generateStream(Poco::JSON::Object &object, int maxStream);
	std::string getValueFromArrayString(std::string arrayString, int indexCount);

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

std::string TempData::getValueFromArrayString(std::string arrayString, int indexCount){
	try{
		Parser parser;
		Var result = parser.parse(arrayString);
		Array::Ptr arr = result.extract<Array::Ptr>();
		Var value = arr->get(indexCount);
		return value.toString();
	}catch(Poco::Exception &e){
		return e.displayText();
	}
}




/**
 * generate snr(sound noise ratio)
 * param [&object : Poco::JSON::Object address]
 * param [key : std:string]
 * param [lower : float -> lowest possible value]
 * param [upper : float -> upper possible value]
 * param [fluctuation : float -> fluctuation (around mean: (lower+upper)/2) possible value]
 * return void
 **/
void TempData::generateSnr(Poco::JSON::Object &object, std::string key, float lower, float upper, float fluctuation){
	object.set(key, Mocker::getRandomMeanFloat(lower, upper, fluctuation));
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
void TempData::generateBer(Poco::JSON::Object& object, std::string key, int decimalPlaces, double lower, double upper, double fluctuation) {
	double number = Mocker::getRandomMeanDouble(lower, upper, fluctuation);
	object.set(key, Poco::format("%0.1E", number/pow10(decimalPlaces)));
}

/**
 * generate rssi(received signal strength indicator)
 * param [&object : Poco::JSON::Object address]
 * param [key : std:string]
 * param [lower : integer -> lowest possible value]
 * param [upper : integer -> upper possible value]
 * param [fluctuation : integer -> fluctuation (around mean: (lower+upper)/2) possible value]
 * return void
 **/
void TempData::generateRssi(Poco::JSON::Object& object, std::string key, int lower, int upper, int fluctuation) {
	object.set(key, Mocker::getRandomMeanInteger(lower, upper, fluctuation));
}

/**
 * generate through-put (amount of data transfered)
 * param [&object : Poco::JSON::Object address]
 * param [key : std:string]
 * param [lower : integer -> lowest possible value]
 * param [upper : integer -> upper possible value]
 * param [fluctuation : integer -> fluctuation (around mean: (lower+upper)/2) possible value]
 * return void
 **/
void TempData::generateThroughput(Poco::JSON::Object& object, std::string key, long lower, long upper, long fluctuation) {
	object.set(key, Mocker::getRandomMeanLong(lower, upper, fluctuation));
}


/**
 * generate correctable(sound noise ratio)
 * param [&object : Poco::JSON::Object address]
 * param [key : std:string]
 * param [lower : float -> lowest possible value]
 * param [upper : float -> upper possible value]
 * param [fluctuation : float -> fluctuation (around mean: (lower+upper)/2) possible value]
 * return void
 **/
void TempData::generateCorrectable(Poco::JSON::Object &object, std::string key, float lower, float upper, float fluctuation){
	object.set(key, Mocker::getRandomMeanFloat(lower, upper, fluctuation));
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
 * generate static string data
 * param [&object : Poco::JSON::Object address]
 * param [key : std:string]
 * return void
 **/
void TempData::generateStaticData(Poco::JSON::Object& object, int choice) {
	int index = this->date.second();
//	cout << index <<  endl;
	switch(choice){
		case CONNECTION_STATUS:
			object.set("connection-status", this->pConf->getString("connection-status"));
			break;
		case CONNECTION_PII:
			object.set("connection-pii", this->pConf->getString("connection-pii"));
			break;
		case VERSION_HW:
			object.set("version-hw", this->pConf->getString("version-hw"));
			break;
		case VERSION_SW:
			object.set("version-sw", this->pConf->getString("version-sw"));
			break;
		case CONNECTION_IP:
			object.set("connection-ip", this->pConf->getString("connection-ip"));
			break;
		case CONNECTION_SSID:
			object.set("connection-ssid", this->pConf->getString("connection-ssid"));
			break;
		case CONNECTION_ROLE:
			object.set("connection-role", this->pConf->getString("connection-role"));
			break;
		case BANDWIDTH:
			object.set("bandwidth", this->pConf->getString("bandwidth"));
			break;
		case BANDWIDTH_STATUS:
			object.set("bandwidth-status", this->pConf->getString("bandwidth-status"));
			break;
		case FREQUENCY:
			object.set("frequency", this->pConf->getString("frequency"));
			break;
		case TDDSCHEDULE:
			object.set("tDDSchedule", this->pConf->getString("tDDSchedule"));
			break;
		case RADIO_ADMIN_MODE:
			object.set("radio-admin-mode", this->pConf->getString("radio-admin-mode"));
			break;
		case WIRELESS_RADIO_TX_POWER:
			object.set("wireless-radio-tx-power", this->pConf->getString("wireless-radio-tx-power"));
			break;
		case WIRELESS_RADIO_STATUS_TX_POWER:
			object.set("wireless-radio-status-tx-power", this->pConf->getString("wireless-radio-status-tx-power"));
			break;
		case HUB_STATE:
			object.set("hub-state", this->getValueFromArrayString(this->pConf->getString("hub-state"), index));//Fetching from array
			break;
		case HUB_RCV_GAIN_LEVEL:
			object.set("hub-rcv-gain-level", this->pConf->getString("hub-rcv-gain-level"));
			break;
		case WIRELESS_MODE:
			object.set("wireless-mode", this->pConf->getString("wireless-mode"));
			break;
		case CPE_O_1:
			object.set("cpe-0-1", this->pConf->getString("cpe-0-1"));
			break;
		case CPE_1_2:
			object.set("cpe-1-2", this->pConf->getString("cpe-1-2"));
			break;
		case BEAM_ID:
			object.set("beam-id", this->pConf->getString("beam-id"));
			break;
		case CPE_1_STATE:
			object.set("cpe-1-state", this->pConf->getString("cpe-1-state"));
			break;
		case CPE_2_STATE:
			object.set("cpe-2-state", this->pConf->getString("cpe-2-state"));
			break;
		case THR_MAX_CAPI:
			object.set("throughput-max-capacity", this->pConf->getString("throughput-max-capacity"));
			break;
		case THR_BEAM_CAP:
			object.set("throughput-beam-capacity", this->pConf->getString("throughput-beam-capacity"));
			break;
		default:
			break;
	}

}


void TempData::generateStream(Poco::JSON::Object &object, int maxStream){
	int i = 0;

	Poco::JSON::Array streamCount;

	for(;i < maxStream; i++){

		Poco::JSON::Object stream;
		stream.set("id", i);
		streamCount.add(stream);

		generateBer(object, Poco::format("ber-curr-%d", i), TempData::s_instance->pConf->getInt("ber-curr.decimal"), TempData::s_instance->pConf->getInt("ber-curr.lower"), TempData::s_instance->pConf->getInt("ber-curr.upper"), TempData::s_instance->pConf->getInt("ber-curr.fluctuaton"));
		generateBer(object, Poco::format("ber-cum-%d", i), TempData::s_instance->pConf->getInt("ber-cum.decimal"), TempData::s_instance->pConf->getInt("ber-cum.lower"), TempData::s_instance->pConf->getInt("ber-cum.upper"), TempData::s_instance->pConf->getInt("ber-cum.fluctuaton"));
		generateCorrectable(object, Poco::format("cw_correctable-%d", i), Mocker::getFloat(TempData::s_instance->pConf->getString("cw_correctable.lower")), Mocker::getFloat(TempData::s_instance->pConf->getString("cw_correctable.upper")), Mocker::getFloat(TempData::s_instance->pConf->getString("cw_correctable.fluctuaton")));
		generateCorrectable(object, Poco::format("cw_uncorrectable-%d", i), Mocker::getFloat(TempData::s_instance->pConf->getString("cw_uncorrectable.lower")), Mocker::getFloat(TempData::s_instance->pConf->getString("cw_uncorrectable.upper")), Mocker::getFloat(TempData::s_instance->pConf->getString("cw_uncorrectable.fluctuaton")));
		generateCorrectable(object, Poco::format("cw_total-%d", i), Mocker::getFloat(TempData::s_instance->pConf->getString("cw_total.lower")), Mocker::getFloat(TempData::s_instance->pConf->getString("cw_total.upper")), Mocker::getFloat(TempData::s_instance->pConf->getString("cw_total.fluctuaton")));
		generateSnr(object, Poco::format("snr-curr-%d", i), Mocker::getFloat(TempData::s_instance->pConf->getString("snr-curr.lower")), Mocker::getFloat(TempData::s_instance->pConf->getString("snr-curr.upper")), Mocker::getFloat(TempData::s_instance->pConf->getString("snr-curr.fluctuaton")));
		generateSnr(object, Poco::format("snr-avg-%d", i), Mocker::getFloat(TempData::s_instance->pConf->getString("snr-avg.lower")), Mocker::getFloat(TempData::s_instance->pConf->getString("snr-avg.upper")), Mocker::getFloat(TempData::s_instance->pConf->getString("snr-avg.fluctuaton")));
		generateSnr(object, Poco::format("snr-min-%d", i), Mocker::getFloat(TempData::s_instance->pConf->getString("snr-min.lower")), Mocker::getFloat(TempData::s_instance->pConf->getString("snr-min.upper")), Mocker::getFloat(TempData::s_instance->pConf->getString("snr-min.fluctuaton")));
		generateSnr(object, Poco::format("snr-max-%d", i), Mocker::getFloat(TempData::s_instance->pConf->getString("snr-max.lower")), Mocker::getFloat(TempData::s_instance->pConf->getString("snr-max.upper")), Mocker::getFloat(TempData::s_instance->pConf->getString("snr-max.fluctuaton")));
		generateThroughput(object, Poco::format("throughput-rx-dput-%d", i), Mocker::getLong(TempData::s_instance->pConf->getString("throughput-rx-dput.lower")), Mocker::getLong(TempData::s_instance->pConf->getString("throughput-rx-dput.upper")), Mocker::getLong(TempData::s_instance->pConf->getString("throughput-rx-dput.fluctuaton")));
		generateThroughput(object, Poco::format("throughput-rx-tput-%d", i), Mocker::getLong(TempData::s_instance->pConf->getString("throughput-rx-tput.lower")), Mocker::getLong(TempData::s_instance->pConf->getString("throughput-rx-tput.upper")), Mocker::getLong(TempData::s_instance->pConf->getString("throughput-rx-tput.fluctuaton")));
		generateThroughput(object, Poco::format("throughput-tx-dput-%d", i), Mocker::getLong(TempData::s_instance->pConf->getString("throughput-tx-dput.lower")), Mocker::getLong(TempData::s_instance->pConf->getString("throughput-tx-dput.upper")), Mocker::getLong(TempData::s_instance->pConf->getString("throughput-tx-dput.fluctuaton")));
		generateThroughput(object, Poco::format("throughput-tx-tput-%d", i), Mocker::getLong(TempData::s_instance->pConf->getString("throughput-tx-tput.lower")), Mocker::getLong(TempData::s_instance->pConf->getString("throughput-tx-tput.upper")), Mocker::getLong(TempData::s_instance->pConf->getString("throughput-tx-tput.fluctuaton")));
		generateThroughput(object, Poco::format("throughput-rx-frames-%d", i), Mocker::getLong(TempData::s_instance->pConf->getString("throughput-rx-frames.lower")), Mocker::getLong(TempData::s_instance->pConf->getString("throughput-rx-frames.upper")), Mocker::getLong(TempData::s_instance->pConf->getString("throughput-rx-frames.fluctuaton")));
		generateThroughput(object, Poco::format("throughput-tx-frames-%d", i), Mocker::getLong(TempData::s_instance->pConf->getString("throughput-tx-frames.lower")), Mocker::getLong(TempData::s_instance->pConf->getString("throughput-tx-frames.upper")), Mocker::getLong(TempData::s_instance->pConf->getString("throughput-tx-frames.fluctuaton")));
		generateThroughput(object, Poco::format("throughput-rx-errorrate-%d", i), Mocker::getLong(TempData::s_instance->pConf->getString("throughput-rx-errorrate.lower")), Mocker::getLong(TempData::s_instance->pConf->getString("throughput-rx-errorrate.upper")), Mocker::getLong(TempData::s_instance->pConf->getString("throughput-rx-errorrate.fluctuaton")));
		generateThroughput(object, Poco::format("throughput-error-crc-%d", i), Mocker::getLong(TempData::s_instance->pConf->getString("throughput-error-crc.lower")), Mocker::getLong(TempData::s_instance->pConf->getString("throughput-error-crc.upper")), Mocker::getLong(TempData::s_instance->pConf->getString("throughput-error-crc.fluctuaton")));
		generateRssi(object, Poco::format("radio-rssi-%d", i), TempData::s_instance->pConf->getInt("radio-rssi.lower"), TempData::s_instance->pConf->getInt("radio-rssi.upper"), TempData::s_instance->pConf->getInt("radio-rssi.fluctuaton"));
		generateFloat(object, Poco::format("radio-tx-power-%d", i), Mocker::getFloat(TempData::s_instance->pConf->getString("radio-tx-power.lower")), Mocker::getFloat(TempData::s_instance->pConf->getString("radio-tx-power.upper")), Mocker::getFloat(TempData::s_instance->pConf->getString("radio-tx-power.fluctuaton")));
		generateInteger(object, Poco::format("connection-mcs-%d", i), TempData::s_instance->pConf->getInt("connection-mcs.lower"), TempData::s_instance->pConf->getInt("connection-mcs.upper"), TempData::s_instance->pConf->getInt("connection-mcs.fluctuaton"));
		generateFloat(object, Poco::format("tx-attenuation-%d", i), Mocker::getFloat(TempData::s_instance->pConf->getString("tx-attenuation.lower")), Mocker::getFloat(TempData::s_instance->pConf->getString("tx-attenuation.upper")), Mocker::getFloat(TempData::s_instance->pConf->getString("tx-attenuation.fluctuaton")));
	}
	object.set("streams-count", streamCount);

	generateStaticData(object, BANDWIDTH);
	generateStaticData(object, BANDWIDTH_STATUS);
	generateStaticData(object, CONNECTION_IP);
	generateStaticData(object, CONNECTION_PII);
	generateStaticData(object, CONNECTION_ROLE);
	generateStaticData(object, CONNECTION_SSID);
	generateStaticData(object, CONNECTION_STATUS);
	generateStaticData(object, FREQUENCY);
	generateStaticData(object, HUB_RCV_GAIN_LEVEL);
	generateStaticData(object, HUB_STATE);
	generateStaticData(object, RADIO_ADMIN_MODE);
	generateStaticData(object, TDDSCHEDULE);
	generateStaticData(object, VERSION_HW);
	generateStaticData(object, VERSION_SW);
	generateStaticData(object, WIRELESS_MODE);
	generateStaticData(object, WIRELESS_RADIO_STATUS_TX_POWER);
	generateStaticData(object, WIRELESS_RADIO_TX_POWER);
	generateStaticData(object, THR_MAX_CAPI);
	generateStaticData(object, THR_BEAM_CAP);

}

#endif /* OTFS_SRC_APP_DASHBOARD_TEST_TEMPDATA_H_ */
