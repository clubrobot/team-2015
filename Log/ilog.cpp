/*
 * ilog.cpp
 *
 *  Created on: Nov 12, 2015
 *      Author: gabriel
 */

#include "ilog.h"

ilog::ilog() {
	// TODO Auto-generated constructor stub

}

ilog::~ilog() {
	// TODO Auto-generated destructor stub
}

std::string ilog::timestamp(){

	std::ostringstream stream;
	time_t rawtime;
	tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime( &rawtime );

	stream << timeinfo->tm_hour <<"h "<<timeinfo->tm_min<<"mn "<<timeinfo->tm_sec <<"s";
	// The str() function of output stringstreams return a std::string
	return stream.str();
}
