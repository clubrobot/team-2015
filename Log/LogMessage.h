/*
 * LogMessage.h
 *
 *  Created on: 27 nov. 2015
 *      Author: ethel
 */

#ifndef LOG_LOGMESSAGE_H_
#define LOG_LOGMESSAGE_H_

#include <string>

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
	std::string time;
	uint8_t memitter; // The emitter's id.
	std::string information;

public:
	LogMessage();
	virtual ~LogMessage();
	//	const NvjLogSeverity& l, const std::string& m, const std::string &details

	// Get the log message's TAG
	Tag getTAG();

	// Set the log message's TAG
	void setTAG(Tag tag);

	// Get the log message's emitter.
	uint8_t getEmitter() const;

	// Set the log message's emitter.
	void setEmitter( uint8_t emitter );

	// Set the log message's date of emission.
	void setTime(std::string time);

	// Get the log message's date of emission.
	std::string getTime();

	// Set the log message's information by erasing the previous one.
	void setInfo(std::string information);

	// Add some new information to the message's one.
	void appendInfo(std::string information);

	// Get the log message's information.
	std::string getInfo();

	// Get the length of the entire log message.
	int getLogLength() const;

};

#endif /* LOG_LOGMESSAGE_H_ */
