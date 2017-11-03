/*
 * System.hpp
 *
 *  Created on: 19-Jul-2017
 *      Author: ubuntu
 */

#ifndef OTFS_SRC_APP_DASHBOARD_SRC_UTIL_SYSTEM_HPP_
#define OTFS_SRC_APP_DASHBOARD_SRC_UTIL_SYSTEM_HPP_
#include "Poco/Environment.h"
#include "Poco/Path.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/NumberFormatter.h"
#include "Poco/JSON/Object.h"
#include <sys/sysinfo.h>
#include <sys/statvfs.h>

using namespace std;
using Poco::Environment;
using Poco::Path;
using Poco::JSON::Object;
struct sysinfo si;
struct statvfs sd;

/**
 * add ram info , current values, in MB
 * @param object
 */
void printRamInfo(Object& object){

	sysinfo (&si);
	object.set("sys-uptime", si.uptime);
	object.set("mem-total-ram", si.totalram/(1024 * 1024));
	object.set("mem-free-ram", si.freeram/(1024 * 1024));
}

/**
 * add cpu info, current info
 */
void printCPUInfo(){

	cout << "Processor "<< sysconf(_SC_NPROCESSORS_ONLN) << endl; /* Number of processesor */
	cout << "CPU TIME "<< sysconf(_SC_CPUTIME) << endl;/* CPU TIME */

}

/**
 * add system info
 * @param object
 */
void printSysInfo(Object& object){

	object.set("os-name", Environment::osName());
	object.set("os-version", Environment::osVersion());
	object.set("os-architecture", Environment::osArchitecture());
	object.set("node-name", Environment::nodeName());
	object.set("node-id", Environment::nodeId());
	object.set("sys-cpu-count", Environment::processorCount());
	object.set("sys-home", Path::home());
	object.set("date-time", Poco::DateTimeFormatter::format(Poco::DateTime(), Poco::DateTimeFormat::ISO8601_FORMAT));

}

/**
 * add system drive info, in MB
 * @param object
 */
void printSysDsk(Object& object){

	if((statvfs("/",&sd)) < 0 ) {
			object.set("dsk-failed-fetch" , "/");
	} else {
		//	object.set("dsk-block-size" , sd.f_bsize);
			object.set("dsk-total-size" , (sd.f_blocks * sd.f_bsize)/(1024 * 1024));
			object.set("dsk-free-size" , (sd.f_bfree * sd.f_bsize)/(1024 * 1024));
		//	object.set("dsk-used-size" , ((sd.f_blocks - sd.f_bfree) * sd.f_bsize)/(1024 * 1024));
	}
}




#endif /* OTFS_SRC_APP_DASHBOARD_SRC_UTIL_SYSTEM_HPP_ */
