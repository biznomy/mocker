/*
 * mocker.h
 *
 *  Created on: 11-Sep-2017
 *      Author: ubuntu
 */

#ifndef OTFS_SRC_APP_DASHBOARD_TEST_MOCKER_H_
#define OTFS_SRC_APP_DASHBOARD_TEST_MOCKER_H_

/**
 * Random Value with in Range logic
 * lowerValue + (rand() % (upperValue - lowerValue + 1));
 **/
#include <random>
#include <cstdio>
#include <stdlib.h>     /* strtof */
using namespace std;


/**
 * 	template method for generating random value
 *	param min (number) : lower bound value
 * 	param max (number) : upper bound value
 * 	return random value : number type
 **/
template <typename T>
T getRandom(T min, T max){
	T div = RAND_MAX /(max - min);
    return min + (rand()/div);
}

/**
 * 	template method for generating random value with small fluctuation
 *	param min (number) : lower bound value
 * 	param max (number) : upper bound value
 * 	return random value : number type
 **/
template <typename T>
T getRandom(T min, T max, T fluctuation){
	T newMin = min + (max - min)/2 - fluctuation;
	T newMax = min + (max - min)/2 + fluctuation;
	T div = RAND_MAX /(newMax - newMin);
    return newMin + (rand()/div);
}

/**
 * 	template method for generating precision value of 2 decimal value
 * 	param number : upper bound value
 * 	return precision value : number
 **/
template <typename T>
T setPrecision(T number){
	char buffer[1024];
	sprintf(buffer, "%.2lf", number);
	return strtof (buffer, NULL);;
}


class Mocker {
public :
	~Mocker();
	static std::string sayHello();
	//Full Fluctuated methods
	static int getRandomInteger(int lowerValue, int upperValue);
	static float getRandomFloat(float lowerValue, float upperValue);
	static double getRandomDouble(double lowerValue, double upperValue);
	static long getRandomLong(long lowerValue, long upperValue);
	//Range Fluctuated methods
	static int getRandomMeanInteger(int lowerValue, int upperValue, int fluctuation);
	static float getRandomMeanFloat(float lowerValue, float upperValue, float fluctuation);
	static double getRandomMeanDouble(double lowerValue, double upperValue, double fluctuation);
	static long getRandomMeanLong(long lowerValue, long upperValue, long fluctuation);
	//
	static long getLong(std::string value);
	static float getFloat(std::string value);
	static int getInt(std::string value);
	static double getDouble(std::string value);

private :
	Mocker();
};

std::string Mocker::sayHello(){
	std::string s = "Hello World !!";
	return s;
}

Mocker::~Mocker(){
	//TODO
}
/**
 * 	static method of mocker class
 *	generate Random integer value with in lower bound value and upper bound value
 * 	params lowerValue : lower bound value
 * 	params upperValue : upper bound value
 * 	return random value : integer
 **/
int Mocker::getRandomInteger(int lowerValue, int upperValue){
	return getRandom(lowerValue, upperValue);
}

/**
 * 	static method of mocker class
 *	generate Random float value with in lower bound value and upper bound value
 * 	param lowerValue : lower bound value
 * 	param upperValue : upper bound value
 * 	return random value : float with 2 decimal precision
 **/
float Mocker::getRandomFloat(float lowerValue, float upperValue){
	float number = getRandom(lowerValue, upperValue);
	return setPrecision(number);
}

/**
 * 	static method of mocker class
 *	generate Random double value with in lower bound value and upper bound value
 * 	param lowerValue : lower bound value
 * 	param upperValue : upper bound value
 * 	return random value : double
 **/
double Mocker::getRandomDouble(double lowerValue, double upperValue){
	return getRandom(lowerValue, upperValue);
}

/**
 * 	static method of mocker class
 *	generate Random long value with in lower bound value and upper bound value
 * 	param lowerValue : lower bound value
 * 	param upperValue : upper bound value
 * 	return random value : long
 **/
long Mocker::getRandomLong(long lowerValue, long upperValue){
	return getRandom(lowerValue, upperValue);
}

/**
 * 	static method of mocker class
 *	generate Random integer value with in (lower bound value and upper bound) mean value having fluctuation value
 * 	param lowerValue : lower bound value
 * 	param upperValue : upper bound value
 * 	return random value : integer
 **/
int Mocker::getRandomMeanInteger(int lowerValue, int upperValue, int fluctuation){
	return getRandom(lowerValue, upperValue, fluctuation);
}

/**
 * 	static method of mocker class
 *	generate Random float value with in (lower bound value and upper bound) mean value having fluctuation value
 * 	param lowerValue : lower bound value
 * 	param upperValue : upper bound value
 * 	return random value : float
 **/
float Mocker::getRandomMeanFloat(float lowerValue, float upperValue, float fluctuation){
	float temp = getRandom(lowerValue, upperValue, fluctuation);
	return setPrecision(temp);
}

/**
 * 	static method of mocker class
 *	generate Random double value with in (lower bound value and upper bound) mean value having fluctuation value
 * 	param lowerValue : lower bound value
 * 	param upperValue : upper bound value
 * 	return random value : double
 **/
double Mocker::getRandomMeanDouble(double lowerValue, double upperValue, double fluctuation){
	return getRandom(lowerValue, upperValue, fluctuation);
}


/**
 * 	static method of mocker class
 *	generate Random long value with in (lower bound value and upper bound) mean value having fluctuation value
 * 	param lowerValue : lower bound value
 * 	param upperValue : upper bound value
 * 	return random value : long
 **/
long Mocker::getRandomMeanLong(long lowerValue, long upperValue, long fluctuation){
	return getRandom(lowerValue, upperValue, fluctuation);
}

/**
 * 	static method of mocker class
 * 	param : string
 * 	return value : long
 **/
long Mocker::getLong(std::string value){
	return (long) std::atol(value.c_str());
}

/**
 * 	static method of mocker class
 * 	param : string
 * 	return value : float
 **/
float Mocker::getFloat(std::string value){
	return (float) std::atof(value.c_str());
}

/**
 * 	static method of mocker class
 * 	param : string
 * 	return value : int
 **/
int Mocker::getInt(std::string value){
	return (int) std::atoi(value.c_str());
}

/**
 * 	static method of mocker class
 * 	param : string
 * 	return value : double
 **/
double Mocker::getDouble(std::string value){
	return (double) std::atof(value.c_str());
}

#endif /* OTFS_SRC_APP_DASHBOARD_TEST_MOCKER_H_ */
