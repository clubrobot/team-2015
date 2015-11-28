/*
 * olog.h
 *
 *  Created on: Nov 12, 2015
 *      Author: gabriel
 */

#ifndef LOG_OLOG_H_
#define LOG_OLOG_H_

#include <ostream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "olog.h"
#include "LogMessage.h"



class olog: public std::ostream {


public:
	olog();
	virtual ~olog();
	//virtual functions that will be implemented by both logfile and logstdout
	virtual void append(LogMessage message) = 0;


};

#endif /* LOG_OLOG_H_ */
