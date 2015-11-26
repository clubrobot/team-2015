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

typedef enum
{
	NVJ_DEBUG,
	NVJ_INFO,
	NVJ_WARNING,
	NVJ_ERROR,
} NvjLogSeverity;


class olog: public std::ostream {
public:
	olog();
	virtual ~olog();
	//virtual functions that will be implemented by both logfile and logstdout
	virtual void append(const NvjLogSeverity& l, const std::string& m, const std::string &details) = 0;

	std::string timestamp();

};

#endif /* LOG_OLOG_H_ */
