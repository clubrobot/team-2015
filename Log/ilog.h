/*
 * ilog.h
 *
 *  Created on: Nov 12, 2015
 *      Author: gabriel
 */

#ifndef LOG_ILOG_H_
#define LOG_ILOG_H_

#include <istream>
#include <time.h>
#include <sstream>

class ilog: public std::istream{
public:
	ilog();
	virtual ~ilog();
	void readFile(const char* filename);
};

#endif /* LOG_ILOG_H_ */
