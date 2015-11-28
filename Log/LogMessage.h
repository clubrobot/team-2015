/*
 * LogMessage.h
 *
 *  Created on: 27 nov. 2015
 *      Author: ethel
 */

#ifndef LOG_LOGMESSAGE_H_
#define LOG_LOGMESSAGE_H_

#include <string>
#include <time.h>
#include <ostream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>

typedef enum
{
	NVJ_DEBUG,
	NVJ_INFO,
	NVJ_WARNING,
	NVJ_ERROR,
} Tag;

class LogMessage {

protected:
	Tag mtag;//LogMessage's type
	std::string mtime;
	uint8_t memitter; // The emitter's id.
	std::string information;

public:
	LogMessage();
	virtual ~LogMessage();

	void setInformation(const std::string& information) {
		this->information = information;
	}

	uint8_t getEmitter() const {
		return memitter;
	}

	void setEmitter(uint8_t memitter) {
		this->memitter = memitter;
	}

	Tag getTag() const {
		return mtag;
	}

	void setTag(Tag mtag) {
		this->mtag = mtag;
	}

	const std::string& getTime() const {
		return mtime;
	}


	std::string timestamp();

	// Set the log message's date of emission.
	void setTime();

	const std::string& getInformation() const {
		return information;
	}

	// Add some new information to the message's one.
	void appendInfo(std::string information);

	// Get the length of the entire log message.
	int getLogLength() const;

};

#endif /* LOG_LOGMESSAGE_H_ */
