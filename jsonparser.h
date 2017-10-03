/*
 * jsonparser.h
 *
 *  Created on: 03-Oct-2017
 *      Author: ubuntu
 */

#ifndef JSONPARSER_H_
#define JSONPARSER_H_

#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"
#include "Poco/JSON/ParseHandler.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Query.h"
#include "Poco/JSON/Stringifier.h"
#include "Poco/Util/JSONConfiguration.h"
#include "Poco/AutoPtr.h"

#include <iostream>

using namespace std;
class jsonparser{
public:
	jsonparser();
	virtual ~jsonparser();
	void test(Poco::JSON::Object &object);
private :
	std::string jsonString;


};

jsonparser::jsonparser(){
	//TODO
}

jsonparser::~jsonparser(){
	//TODO
}

void jsonparser::test(Poco::JSON::Object &object){
	std::stringstream ss;
	object.stringify(ss, 2, 2);
	Poco::AutoPtr<Poco::Util::JSONConfiguration> tConf = new Poco::Util::JSONConfiguration(ss);
	cout << tConf->getString("wirelessTrue.wireless.status.rstreams.[1]") << endl;
}




#endif /* JSONPARSER_H_ */
