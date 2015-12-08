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

#define RED  "\x1B[31m"
#define GREEN  "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE  "\x1B[34m"
#define MAGENTA  "\x1B[35m"
#define CYAN  "\x1B[36m"
#define WHITE  "\x1B[37m"

typedef enum
{
	DEBUG,
	INFO,
	WARNING,
	ERROR,
} Tag;



class LogMessage {

protected:
	Tag mtag;//LogMessage's type
	std::string mtime;
	int memitter; // The emitter's id.
	std::string minformation;

public:
	LogMessage();

	void setInformation(const std::string& information) {
		this->minformation = information;
	}

	int getEmitter() const {
		return memitter;
	}

	void setEmitter(int memitter) {
		this->memitter = memitter;
	}

	Tag getTag() const {
		return mtag;
	}

	void setTag(Tag mtag) {
		this->mtag = mtag;
	}

	std::string getStringFromTag();

	const std::string& getTime() const {
		return mtime;
	}


	std::string timestamp();

	// Set the log message's date of emission.
	void setTime();

	const std::string& getInformation() const {
		return minformation;
	}

	// Add some new information to the message's one.
	void appendInfo(std::string information);

	// Get the length of the entire log message.
	int getLogLength() const;

};

#endif /* LOG_LOGMESSAGE_H_ */
