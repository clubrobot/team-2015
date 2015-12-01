/*
 * LogMessage.cpp
 *
 *  Created on: 27 nov. 2015
 *      Author: ethel
 */

#include "LogMessage.h"

LogMessage::LogMessage() {
	// TODO Auto-generated constructor stub
	mtag = {};
	minformation = "";
	memitter=0;
	mtime ="";
}

LogMessage::~LogMessage() {
	// TODO Auto-generated destructor stub
}

std::string LogMessage::timestamp(){

	std::ostringstream stream;
	time_t rawtime;
	tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime( &rawtime );

	stream << timeinfo->tm_hour <<"h "<<timeinfo->tm_min<<"mn "<<timeinfo->tm_sec <<"s";
	// The str() function of output stringstreams return a std::string
	return stream.str();
}

void LogMessage::setTime(){
	mtime = timestamp();
}
