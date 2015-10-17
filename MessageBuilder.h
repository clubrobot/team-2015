/*
 * MessageBuilder.h
 *
 *  Created on: Oct 8, 2015
 *      Author: gabriel
 */

#ifndef MESSAGEBUILDER_H_
#define MESSAGEBUILDER_H_

#include <cstring>
#include <queue>

#include "Message.h"

class MessageBuilder {
public:
	MessageBuilder();
	virtual ~MessageBuilder();

	void appendRawData(uint8_t* data, int len);

	bool newMessagesCompleted() { return mmsgqueue.size() > 0;}
	Message retrieveMessage();
private:
	std::queue<Message> mmsgqueue;
	Message mcurrentMsg;
	bool mcollecting;
	int moffset;
	uint8_t mlsbyte;
};

#endif /* MESSAGEBUILDER_H_ */
