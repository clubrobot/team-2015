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

void LogMessage::appendInfo(std::string information) {
	minformation += information;
}

std::string LogMessage::getStringFromTag() {
	switch(mtag)
	{
	case DEBUG: return "DEBUG";
	case INFO: return "INFO";
	case WARNING: return "WARNING";
	case ERROR: return "ERROR";
	default: return "the tag isn't correct";
	}
}

int LogMessage::getLogLength() const {
	return sizeof(this);
}

void LogMessage::appendData(uint8_t *data, uint8_t size){
	std::ostringstream ss;//used to retrieve string from uint8_t*

	for( int i=0;i<size;i++ )
	{
		ss << std::setw(2) << (unsigned int)data[i];
	}
	this->setInformation(ss.str());
}

