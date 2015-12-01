/*
 * logfile.h
 *
 *  Created on: 26 nov. 2015
 *      Author: ethel
 */

#ifndef LOG_LOGFILE_H_
#define LOG_LOGFILE_H_


#include <fstream>
#include <iostream>
#include "olog.h"
#include "LogMessage.h"

class LogFile: public olog {
public:
	LogFile(char *name);
	~LogFile();

	void append(LogMessage);

private:
	std::string filename; //path will be /var/log/logdaemon.txt
	std::ofstream *file;

};


#endif /* LOG_LOGFILE_H_ */

