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
#include <iomanip>

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

	int getEmitter() const;
	Tag getTag() const;

	const std::string& getInformation()const;

	const std::string& getTime()const;

	void setEmitter(int memitter) {
		this->memitter = memitter;
	}

	void setTag(Tag mtag) {
		this->mtag = mtag;
	}

	std::string getStringFromTag();



	std::string timestamp();

	// Set the log message's date of emission.
	void setTime();


	// Add some new information to the message's one.
	void appendInfo(std::string information);

	// Get the length of the entire log message.
	int getLogLength() const;

	//appendData from a uint8_t tab.
	void appendData(uint8_t *data, uint8_t size);


};

inline Tag LogMessage::getTag()const
{ return mtag; }

inline int LogMessage::getEmitter() const
{return memitter;}

inline const std::string& LogMessage::getInformation() const
{return minformation;}

inline const std::string& LogMessage::getTime() const
{return mtime;}



#endif /* LOG_LOGMESSAGE_H_ */
