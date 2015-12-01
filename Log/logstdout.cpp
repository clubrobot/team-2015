/*
 * logstdout.cpp
 *
 *  Created on: 26 nov. 2015
 *      Author: ethel
 */

#include "logstdout.h"

logstdout::logstdout() {
	// TODO Auto-generated constructor stub

}

logstdout::~logstdout() {
	// TODO Auto-generated destructor stub
}


void logstdout::append(LogMessage message) {
	std::string tag = message.getStringFromTag();
	std::string info = message.getInformation();
	std::string date = message.getTime();
	uint8_t emitter = message.getEmitter();

	switch (message.getTag())
	{
	case DEBUG:
	case WARNING:
	case INFO:
		std::cout << emitter << "has sent";
		std::cout << Color(FG_GREEN) << info.c_str();
		std::cout << "the " << date << std::endl;
		break;
	case ERROR:
	default:
		std::cerr << Color(FG_RED)<< info.c_str();
		break;
	}
}

