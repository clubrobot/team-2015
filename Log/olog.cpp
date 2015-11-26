/*
 * olog.cpp
 *
 *  Created on: Nov 12, 2015
 *      Author: gabriel
 */

#include "olog.h"

olog::olog() {
	// TODO Auto-generated constructor stub

}

olog::~olog() {
	// TODO Auto-generated destructor stub
}


std::string olog::timestamp(){

	std::ostringstream stream;
	time_t rawtime;
	tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime( &rawtime );

	stream << timeinfo->tm_hour <<"h "<<timeinfo->tm_min<<"mn "<<timeinfo->tm_sec <<"s";
	// The str() function of output stringstreams return a std::string
	return stream.str();
}
