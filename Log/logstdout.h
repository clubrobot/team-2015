/*
 * logstdout.h
 *
 *  Created on: 26 nov. 2015
 *      Author: ethel
 */

#ifndef LOG_LOGSTDOUT_H_
#define LOG_LOGSTDOUT_H_

#include "olog.h"


class logstdout: public olog {
public:
	logstdout();
	virtual ~logstdout();
	void append(const NvjLogSeverity& l, const std::string& m, const std::string &details="");
};
#endif /* LOG_LOGSTDOUT_H_ */

