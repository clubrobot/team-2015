/*
 * MessageBuilder.h
 *
 *  Created on: Oct 8, 2015
 *      Author: gabriel
 */

#ifndef MESSAGEBUILDER_H_
#define MESSAGEBUILDER_H_

#include <cstring>
#include <stack>

#include "Message.h"

class MessageBuilder {
public:
	MessageBuilder();
	virtual ~MessageBuilder();

	void appendRawData(uint8_t* data, int len);

	bool newMessagesCompleted() { return mmsgstack.size() > 0;}
	Message retrieveMessage();
private:
	std::stack<Message> mmsgstack;
	Message mcurrentMsg;
	bool mcollecting;
	int moffset;
	uint8_t mlsbyte;
};

#endif /* MESSAGEBUILDER_H_ */
