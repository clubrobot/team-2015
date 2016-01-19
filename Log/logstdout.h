/*
 * logstdout.h
 *
 *  Created on: 26 nov. 2015
 *      Author: ethel
 */

#ifndef LOG_LOGSTDOUT_H_
#define LOG_LOGSTDOUT_H_

#include "olog.h"
#include "LogMessage.h"
#include "Color.h"

typedef enum
{
	ODEBUG,
	OINFO,
	OWARNING,
	OERROR,
} OutType;

class logstdout: public olog {
public:
	logstdout();
	void append(LogMessage logMessage);
	void append(const Tag& tag, LogMessage& logMessage);

};
#endif /* LOG_LOGSTDOUT_H_ */

