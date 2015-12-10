/*
 * logstdout.cpp
 *
 *  Created on: 26 nov. 2015
 *      Author: ethel
 */

#include "logstdout.h"

logstdout::logstdout() {
	this->rdbuf(std::cout.rdbuf());//we choose cout to direct display messages
}

void logstdout::append(LogMessage message) {
	std::string tag = message.getStringFromTag();
	std::string info = message.getInformation();
	std::string date = message.getTime();
	int emitter = message.getEmitter();

	switch (message.getTag())
	{
	case DEBUG:
		*this <<Color(FG_BLUE)<< "[Debug] from " << emitter <<" "<<info;
		*this << " at " << date << "\n";
		break;
	case WARNING:
		*this <<Color(FG_RED)<< "[Warning] from " << emitter <<" "<< info;
		*this << " at " << date << "\n";
		break;
	case INFO:
		*this <<Color(FG_GREEN)<< "[Info] from "<< emitter << " has sent:";
		*this <<info;
		*this << " at " << date << "\n";
		break;
	case ERROR:
	default:
		*this <<Color(FG_RED)<<"[Error] from "<< emitter <<" "<< info;
		*this << " at " << date << "\n";
		break;
	}
	*this <<Color(FG_DEFAULT);

}

