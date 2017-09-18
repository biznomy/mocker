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

using Poco::JSON::Parser;
using Poco::JSON::Object;
using Poco::JSON::Array;
using Poco::Dynamic::Var;

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
	static void generateSnr(Poco::JSON::Object &object, std::string key, float lower, float upper, float fluctuation);
	static void generateBer(Poco::JSON::Object &object, std::string key, int decimalPlaces, double lower, double upper, double fluctuation);
	static void generateRssi(Poco::JSON::Object &object, std::string key, int lower, int upper, int fluctuation);
	static void generateThroughput(Poco::JSON::Object &object, std::string key, long lower, long upper, long fluctuation);
	static void generateCorrectable(Poco::JSON::Object &object, std::string key, float lower, float upper, float fluctuation);

public :
	Poco::DateTime date;
	virtual ~TempData();
	static Poco::AutoPtr<Poco::Util::JSONConfiguration> pConf ;
	static void generateInteger(Poco::JSON::Object &object, std::string key, int lower, int upper, int fluctuation);
	static void generateFloat(Poco::JSON::Object &object, std::string key, float lower, float upper, float fluctuation);
	static void generateLong(Poco::JSON::Object &object, std::string key, long lower, long upper, long fluctuation);
	static void generateDouble(Poco::JSON::Object &object, std::string key, double lower, double upper, double fluctuation);
	//
	void generateStaticData(Poco::JSON::Object &object, int choice);
	static void generateStream(Poco::JSON::Object &object, int maxStream);
	std::string getValueFromArrayString(std::string arrayString, int indexCount);

};



TempData::TempData() {
//	cout << "open object tempData" << endl;
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
		default:
			break;
	}

}


void TempData::generateStream(Poco::JSON::Object &object, int maxStream){
	TempData td;
	int i = 0;
	for(;i < maxStream; i++){

		generateBer(object, Poco::format("ber-curr-%d", i), td.pConf->getInt("ber-curr.decimal"), td.pConf->getInt("ber-curr.lower"), td.pConf->getInt("ber-curr.upper"), td.pConf->getInt("ber-curr.fluctuaton"));
		generateBer(object, Poco::format("ber-cum-%d", i), td.pConf->getInt("ber-cum.decimal"), td.pConf->getInt("ber-cum.lower"), td.pConf->getInt("ber-cum.upper"), td.pConf->getInt("ber-cum.fluctuaton"));
		generateCorrectable(object, Poco::format("cw_correctable-%d", i), Mocker::getFloat(td.pConf->getString("cw_correctable.lower")), Mocker::getFloat(td.pConf->getString("cw_correctable.upper")), Mocker::getFloat(td.pConf->getString("cw_correctable.fluctuaton")));
		generateCorrectable(object, Poco::format("cw_uncorrectable-%d", i), Mocker::getFloat(td.pConf->getString("cw_uncorrectable.lower")), Mocker::getFloat(td.pConf->getString("cw_uncorrectable.upper")), Mocker::getFloat(td.pConf->getString("cw_uncorrectable.fluctuaton")));
		generateCorrectable(object, Poco::format("cw_total-%d", i), Mocker::getFloat(td.pConf->getString("cw_total.lower")), Mocker::getFloat(td.pConf->getString("cw_total.upper")), Mocker::getFloat(td.pConf->getString("cw_total.fluctuaton")));
		generateSnr(object, Poco::format("snr-curr-%d", i), Mocker::getFloat(td.pConf->getString("snr-curr.lower")), Mocker::getFloat(td.pConf->getString("snr-curr.upper")), Mocker::getFloat(td.pConf->getString("snr-curr.fluctuaton")));
		generateSnr(object, Poco::format("snr-avg-%d", i), Mocker::getFloat(td.pConf->getString("snr-avg.lower")), Mocker::getFloat(td.pConf->getString("snr-avg.upper")), Mocker::getFloat(td.pConf->getString("snr-avg.fluctuaton")));
		generateSnr(object, Poco::format("snr-min-%d", i), Mocker::getFloat(td.pConf->getString("snr-min.lower")), Mocker::getFloat(td.pConf->getString("snr-min.upper")), Mocker::getFloat(td.pConf->getString("snr-min.fluctuaton")));
		generateSnr(object, Poco::format("snr-max-%d", i), Mocker::getFloat(td.pConf->getString("snr-max.lower")), Mocker::getFloat(td.pConf->getString("snr-max.upper")), Mocker::getFloat(td.pConf->getString("snr-max.fluctuaton")));
		generateThroughput(object, Poco::format("throughput-rx-dput-%d", i), Mocker::getLong(td.pConf->getString("throughput-rx-dput.lower")), Mocker::getLong(td.pConf->getString("throughput-rx-dput.upper")), Mocker::getLong(td.pConf->getString("throughput-rx-dput.fluctuaton")));
		generateThroughput(object, Poco::format("throughput-rx-tput-%d", i), Mocker::getLong(td.pConf->getString("throughput-rx-tput.lower")), Mocker::getLong(td.pConf->getString("throughput-rx-tput.upper")), Mocker::getLong(td.pConf->getString("throughput-rx-tput.fluctuaton")));
		generateThroughput(object, Poco::format("throughput-tx-dput-%d", i), Mocker::getLong(td.pConf->getString("throughput-tx-dput.lower")), Mocker::getLong(td.pConf->getString("throughput-tx-dput.upper")), Mocker::getLong(td.pConf->getString("throughput-tx-dput.fluctuaton")));
		generateThroughput(object, Poco::format("throughput-tx-tput-%d", i), Mocker::getLong(td.pConf->getString("throughput-tx-tput.lower")), Mocker::getLong(td.pConf->getString("throughput-tx-tput.upper")), Mocker::getLong(td.pConf->getString("throughput-tx-tput.fluctuaton")));
		generateThroughput(object, Poco::format("throughput-rx-frames-%d", i), Mocker::getLong(td.pConf->getString("throughput-rx-frames.lower")), Mocker::getLong(td.pConf->getString("throughput-rx-frames.upper")), Mocker::getLong(td.pConf->getString("throughput-rx-frames.fluctuaton")));
		generateThroughput(object, Poco::format("throughput-tx-frames-%d", i), Mocker::getLong(td.pConf->getString("throughput-tx-frames.lower")), Mocker::getLong(td.pConf->getString("throughput-tx-frames.upper")), Mocker::getLong(td.pConf->getString("throughput-tx-frames.fluctuaton")));
		generateThroughput(object, Poco::format("throughput-rx-errorrate-%d", i), Mocker::getLong(td.pConf->getString("throughput-rx-errorrate.lower")), Mocker::getLong(td.pConf->getString("throughput-rx-errorrate.upper")), Mocker::getLong(td.pConf->getString("throughput-rx-errorrate.fluctuaton")));
		generateThroughput(object, Poco::format("throughput-error-crc-%d", i), Mocker::getLong(td.pConf->getString("throughput-error-crc.lower")), Mocker::getLong(td.pConf->getString("throughput-error-crc.upper")), Mocker::getLong(td.pConf->getString("throughput-error-crc.fluctuaton")));
		generateRssi(object, Poco::format("radio-rssi-%d", i), td.pConf->getInt("radio-rssi.lower"), td.pConf->getInt("radio-rssi.upper"), td.pConf->getInt("radio-rssi.fluctuaton"));
		generateFloat(object, Poco::format("radio-tx-power-%d", i), Mocker::getFloat(td.pConf->getString("radio-tx-power.lower")), Mocker::getFloat(td.pConf->getString("radio-tx-power.upper")), Mocker::getFloat(td.pConf->getString("radio-tx-power.fluctuaton")));
		generateInteger(object, Poco::format("connection-mcs-%d", i), td.pConf->getInt("connection-mcs.lower"), td.pConf->getInt("connection-mcs.upper"), td.pConf->getInt("connection-mcs.fluctuaton"));
		generateFloat(object, Poco::format("tx-attenuation-%d", i), Mocker::getFloat(td.pConf->getString("tx-attenuation.lower")), Mocker::getFloat(td.pConf->getString("tx-attenuation.upper")), Mocker::getFloat(td.pConf->getString("tx-attenuation.fluctuaton")));
	}


	td.generateStaticData(object, BANDWIDTH);
	td.generateStaticData(object, BANDWIDTH_STATUS);
	td.generateStaticData(object, CONNECTION_IP);
	td.generateStaticData(object, CONNECTION_PII);
	td.generateStaticData(object, CONNECTION_ROLE);
	td.generateStaticData(object, CONNECTION_SSID);
	td.generateStaticData(object, CONNECTION_STATUS);
	td.generateStaticData(object, FREQUENCY);
	td.generateStaticData(object, HUB_RCV_GAIN_LEVEL);
	td.generateStaticData(object, HUB_STATE);
	td.generateStaticData(object, RADIO_ADMIN_MODE);
	td.generateStaticData(object, TDDSCHEDULE);
	td.generateStaticData(object, VERSION_HW);
	td.generateStaticData(object, VERSION_SW);
	td.generateStaticData(object, WIRELESS_MODE);
	td.generateStaticData(object, WIRELESS_RADIO_STATUS_TX_POWER);
	td.generateStaticData(object, WIRELESS_RADIO_TX_POWER);




}

#endif /* OTFS_SRC_APP_DASHBOARD_TEST_TEMPDATA_H_ */
