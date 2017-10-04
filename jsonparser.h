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

Poco::AutoPtr<Poco::Util::JSONConfiguration> request = new Poco::Util::JSONConfiguration("/home/ubuntu/Desktop/whitelist.json");


class Util{

	static Poco::Dynamic::Var getDynamicVar(std::string string);
	static Poco::DynamicStruct getDynamicStruct(Poco::Dynamic::Var var);
	static Poco::JSON::Object::Ptr getObjectPtr(Poco::Dynamic::Var var);
public :
	static bool parseJSONObject(std::string stringVal);
	static bool parseJSONArray(std::string stringVal);
	static std::string stringConvertor(Poco::JSON::Object obj);
	static std::string stringConvertor(Poco::JSON::Array array);
	static Poco::JSON::Object::Ptr jsonConvertor(std::string stringVal);
	static Poco::JSON::Array::Ptr arrayConvertor(std::string stringVal);

	static bool isObject(Poco::JSON::Object::Ptr &object, std::string key);
	static bool isEmpty(Poco::JSON::Object &object, std::string key);
	static bool isEmpty(Poco::JSON::Array &array, std::string key);
	static bool isArray(Poco::JSON::Array &array, std::string key);
	static bool isArray(Poco::JSON::Array::Ptr &array, std::string key);

	static bool isObject(std::string json, std::string key);
	static bool isEmpty(std::string json, std::string key);
	static bool isArray(std::string array, std::string key);

};

bool Util::parseJSONObject(std::string stringVal){
    try{

    	Parser parser;
		Var result = parser.parse(stringVal);
		Poco::JSON::Object::Ptr pObj = result.extract<Object::Ptr>();

    }catch(...){
    	return false;
    }
    return true;
}
bool Util::parseJSONArray(std::string stringVal){
    try{
    	Parser parser;
    	Var result = parser.parse(stringVal);
    	Poco::JSON::Array::Ptr arr = result.extract<Array::Ptr>();

    }catch(...){
    	return false;
    }
    return true;
}

std::string Util::stringConvertor(Poco::JSON::Object obj){
	std::ostringstream os;
	obj.stringify(os, 2);
	return os.str();
}

std::string Util::stringConvertor(Poco::JSON::Array array){
	std::ostringstream os;
	array.stringify(os, 2);
	return os.str();
}

Poco::JSON::Object::Ptr Util::jsonConvertor(std::string stringVal){
	Parser parser;
	Var result = parser.parse(stringVal);
	Object::Ptr pObj = result.extract<Object::Ptr>();
	return pObj;
}

Poco::JSON::Array::Ptr Util::arrayConvertor(std::string stringVal){
	Parser parser;
	Var result = parser.parse(stringVal);
	Array::Ptr arr = result.extract<Array::Ptr>();
	return arr;
}

Poco::Dynamic::Var Util::getDynamicVar(std::string string){
	Poco::JSON::Parser parser;
	Poco::Dynamic::Var result = parser.parse(string);
	return result;
}

Poco::DynamicStruct Util::getDynamicStruct(Poco::Dynamic::Var var){
	return *(getObjectPtr(var));
}
Poco::JSON::Object::Ptr Util::getObjectPtr(Poco::Dynamic::Var var){
	return var.extract<Object::Ptr>();
}

bool Util::isObject(Poco::JSON::Object::Ptr &object, std::string key){
	return object->isObject(key);
}

bool Util::isEmpty(Poco::JSON::Object &object, std::string key){
	return getDynamicStruct(getDynamicVar(stringConvertor(object)))[key].isEmpty();
}

bool Util::isEmpty(Poco::JSON::Array &array, std::string key){
	return getDynamicStruct(getDynamicVar(stringConvertor(array)))[key].isEmpty();
}

bool Util::isArray(Poco::JSON::Array &array, std::string key){
	return getDynamicStruct(getDynamicVar(stringConvertor(array)))[key].isArray();
}

bool Util::isArray(Poco::JSON::Array::Ptr &array, std::string key){
	return array->isArray(key);
}

bool Util::isObject(std::string json, std::string key){
	Poco::JSON::Object::Ptr ptr = getObjectPtr(getDynamicVar(json));
	return ptr->isObject(key);
}

bool Util::isEmpty(std::string json, std::string key){
	return getDynamicStruct(getDynamicVar(json))[key].isEmpty();
}

bool Util::isArray(std::string array, std::string key){
	return getDynamicStruct(getDynamicVar(array))[key].isArray();
}


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
	std::stringstream newJSON, originalJSON;
	object.stringify(newJSON, 2, 2);
	object.stringify(originalJSON, 2, 2);
	Poco::AutoPtr<Poco::Util::JSONConfiguration> newJSONConf = new Poco::Util::JSONConfiguration(newJSON);
	Poco::AutoPtr<Poco::Util::JSONConfiguration> originalJSONConf = new Poco::Util::JSONConfiguration(originalJSON);
	if(request->hasProperty("keys[0].whitelist")){

		std::string  blackListArray = request->getString("keys[0].blacklist");
		cout << "console data :  "<<  blackListArray << endl;
		if(Util::parseJSONArray(blackListArray)){
			Poco::JSON::Array::Ptr tempArray =  Util::arrayConvertor(request->getString("keys[0].blacklist"));
			for(unsigned int i = 0;i < tempArray->size(); i++){

				newJSONConf->remove(tempArray->get(i).toString());
				cout <<  newJSONConf->getString("wirelessTrue") << endl;
			}
		}


		std::string  whiteListArray = request->getString("keys[0].whitelist");
		cout << "console data :  "<<  whiteListArray << endl;
		if(Util::parseJSONArray(whiteListArray)){
			Poco::JSON::Array::Ptr tempArray =  Util::arrayConvertor(request->getString("keys[0].whitelist"));
			for(unsigned int i = 0;i < tempArray->size(); i++){

				newJSONConf->setString(tempArray->get(i).toString(), originalJSONConf->getString(tempArray->get(i).toString()));
				cout <<  newJSONConf->getString("wirelessTrue") << endl;

			}
		}
	}

}






#endif /* JSONPARSER_H_ */
