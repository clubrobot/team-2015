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

void logstdout::append(LogMessage message) {
	std::string tag = message.getStringFromTag();
	std::string info = message.getInformation();
	std::string date = message.getTime();
	uint8_t emitter = message.getEmitter();

	switch (message.getTag())
	{
	case DEBUG:
		std::cout << Color(FG_BLUE)<< "debug message from:" << emitter;
		std::cout << ":" << info.c_str() << std::endl;
		break;
	case WARNING:
		std::cerr << Color(FG_RED)<< "Warning!!"<< info.c_str() << std::endl;
		break;

	case INFO:
		std::cout << Color(FG_GREEN)<< emitter << " has sent:";
		std::cout << info.c_str();
		std::cout << " at " << date << std::endl;
		break;
	case ERROR:
	default:
		std::cerr << Color(FG_RED)<< "ERROR!!"<< info.c_str() << std::endl;
		break;
	}
}

