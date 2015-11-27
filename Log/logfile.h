/*
 * logfile.h
 *
 *  Created on: 26 nov. 2015
 *      Author: ethel
 */

#ifndef LOG_LOGFILE_H_
#define LOG_LOGFILE_H_


#include <fstream>
#include "olog.h"
#include "LogMessage.h"

class LogFile: public olog {
public:
	LogFile(char *f);
	~LogFile();

	void append(LogMessage);

private:
	std::string filename;
	std::ofstream *file;

};


#endif /* LOG_LOGFILE_H_ */
