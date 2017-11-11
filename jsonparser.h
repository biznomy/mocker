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

class Util{

	static Poco::Dynamic::Var getDynamicVar(std::string string);
	static Poco::DynamicStruct getDynamicStruct(Poco::Dynamic::Var var);
public :
	static Poco::JSON::Object::Ptr getObjectPtr(Poco::Dynamic::Var var);
	static Poco::JSON::Array::Ptr getArrayPtr(Poco::Dynamic::Var var);
	static bool parseJSONObject(std::string stringVal);
	static bool parseJSONArray(std::string stringVal);
	static std::string stringConvertor(Poco::JSON::Object obj);
	static std::string stringConvertor(Poco::JSON::Array array);
	static Poco::JSON::Object::Ptr jsonConvertor(std::string stringVal);
	static Poco::JSON::Array::Ptr arrayConvertor(std::string stringVal);

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

Poco::JSON::Array::Ptr Util::getArrayPtr(Poco::Dynamic::Var var){
	return var.extract<Poco::JSON::Array::Ptr>();
}

class jsonparser{
public:
	jsonparser();
	virtual ~jsonparser();
	void test(Poco::JSON::Object &inputJSON, Poco::JSON::Object &outputJSON, std::string &requestJSON);
	void recursuive(Poco::JSON::Object::Ptr& input, Poco::JSON::Object::Ptr output);
};

jsonparser::jsonparser(){
	//
}

jsonparser::~jsonparser(){
	//TODO
}

void jsonparser::test(Poco::JSON::Object &inputJSON, Poco::JSON::Object &outputJSON, std::string &requestJSON){
	std::stringstream newJSON, originalJSON;
	inputJSON.stringify(newJSON, 2, 2);
	inputJSON.stringify(originalJSON, 2, 2);
	Poco::AutoPtr<Poco::Util::JSONConfiguration> newJSONConf = new Poco::Util::JSONConfiguration(newJSON);
	Poco::AutoPtr<Poco::Util::JSONConfiguration> originalJSONConf = new Poco::Util::JSONConfiguration(originalJSON);
	Poco::JSON::Object::Ptr myRequestJSON = Util::jsonConvertor(requestJSON);

	Poco::JSON::Array::Ptr arrayRequest = Util::getArrayPtr(myRequestJSON->get("keys"));
	for(unsigned int i = 0; i < arrayRequest->size(); ++i){

		try{

			Poco::JSON::Object::Ptr requestData = Util::getObjectPtr(arrayRequest->get(i));
			Poco::AutoPtr<Poco::Util::JSONConfiguration> requestJSONConf = new Poco::Util::JSONConfiguration(requestData);
//			cout << "Prefix : " << requestJSONConf->getString("prefix") << endl;


			if(requestJSONConf->hasProperty("blacklist")){

				std::string  blackListArray = requestJSONConf->getString("blacklist");
				if(Util::parseJSONArray(blackListArray)){
					Poco::JSON::Array::Ptr tempArray =  Util::arrayConvertor(blackListArray);
					for(unsigned int i = 0;i < tempArray->size(); i++){
						newJSONConf->remove(tempArray->get(i).toString());
					}
				}
			}//end black-list

			if(requestJSONConf->hasProperty("whitelist")){

				std::string  whiteListArray = requestJSONConf->getString("whitelist");
				if(Util::parseJSONArray(whiteListArray)){
					Poco::JSON::Array::Ptr tempArray =  Util::arrayConvertor(whiteListArray);
					for(unsigned int i = 0;i < tempArray->size(); i++){
						newJSONConf->setString(tempArray->get(i).toString(), originalJSONConf->getString(tempArray->get(i).toString()));
					}
				}
			}//end white-list


			if(Util::parseJSONObject(newJSONConf->getString(requestJSONConf->getString("prefix")))){
				Poco::JSON::Object::Ptr object(Util::jsonConvertor(newJSONConf->getString(requestJSONConf->getString("prefix"))));
				Poco::JSON::Object::Ptr output = new Poco::JSON::Object;
				recursuive(object, output);
				outputJSON.set(requestJSONConf->getString("prefix"), output);
			}


		}catch(Poco::Exception  &e){
			cout << e.displayText() << endl;
		}

	}






}

void jsonparser::recursuive(Poco::JSON::Object::Ptr& input, Poco::JSON::Object::Ptr output){
	Poco::JSON::Object::Iterator it;
	for(it = input->begin(); it != input->end(); it++){
		std::string temp = it->second.toString();
		if(Util::parseJSONObject(temp)){
			Poco::JSON::Object::Ptr newOut = new Poco::JSON::Object;
			Poco::JSON::Object::Ptr oldOut(Util::jsonConvertor(temp));
			this->recursuive(oldOut, newOut);
			try{
				output->set(it->first, newOut);
			}catch(Poco::Exception &e){
				cout << e.displayText()<< endl;
			}
		}else if(Util::parseJSONArray(temp)){

			Poco::JSON::Array::Ptr array = Util::arrayConvertor(temp);
			for(unsigned int i = 0; i < array->size(); i++){
				Poco::JSON::Object::Ptr newOut = new Poco::JSON::Object;
				Poco::JSON::Object::Ptr fromArray = Util::getObjectPtr(array->get(i));
				recursuive(fromArray, newOut);
				array->set(i, newOut);
			}
			output->set(it->first, array);

		} else {
			output->set(it->first, temp);
		}
	}
}


#endif /* JSONPARSER_H_ */