/*
 * ilog.h
 *
 *  Created on: Nov 12, 2015
 *      Author: gabriel
 */

#ifndef LOG_ILOG_H_
#define LOG_ILOG_H_

#include <istream>

class ilog: public std::istream {
public:
	ilog();
	virtual ~ilog();
};

#endif /* LOG_ILOG_H_ */
