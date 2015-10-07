/*
 * Parser.h
 *
 *  Created on: 6 oct. 2015
 *      Author: ethel
 */

#ifndef PARSER_H_
#define PARSER_H_
#include "Message.h"
#include <list>

struct objectList{
	void* ptr;
	int nb;
};

class Parser{
public:
	Parser();
	virtual ~Parser();
	void putInt(int data);
	void putFloat(float data);
	int getInt();
	float getFloat();
	void putData(const void*, int);
	void getData(void*, int);
	void commit();
	void open(Message* msg);

protected:
	Message* mmesg;
	std::list<objectList> mlist;//liste d'objecttList

};



#endif /* PARSER_H_ */
