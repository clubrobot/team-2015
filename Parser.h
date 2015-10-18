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


class Parser{
public:
	Parser();
	virtual ~Parser();
	void putInt(int & data);
	void putFloat(float & data);
	int getInt();
	float getFloat();
	void putData(void*, int);
	void getData(void* data, int nb);
	void commit();
	void open(Message* msg);
	void rewind();

	struct ParsingObject{
		void* ptr;
		int nb;
	};
protected:
	Message* mmesg;
	int moffset;
	std::list<ParsingObject>mlist;//liste d'objecttList

};



#endif /* PARSER_H_ */
