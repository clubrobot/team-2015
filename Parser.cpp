/*
 * Parser.cpp
 *
 *  Created on: 6 oct. 2015
 *      Author: ethel
 */

#include "Parser.h"

Parser::Parser() {
	// TODO Auto-generated constructor stub
	mmesg = nullptr;
	moffset =0;
	mlist.clear();
}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}

void Parser::putInt(int data){
	putData(&data, sizeof(int));
}

void Parser::putFloat(float data){
	putData(&data, sizeof(float));
}


int Parser::getInt(){
	int* lastint = nullptr;
	getData(lastint,1);
	int result = *(lastint+moffset);
	moffset++;
	return result;
}

float Parser::getFloat(){
	float* lastfloat = nullptr;
	getData(lastfloat,1);
	float result = *(lastfloat+moffset);
	moffset++;
	return result;
}

void Parser::putData(void* data, int nb){
	ParsingObject structData;
	structData.ptr = data;
	structData.nb = nb;
	mlist.push_front(structData);
}

void Parser::getData(void* data, int nb){
	void* datacopy = mmesg->getData();
	memcpy(data,datacopy,nb);
	moffset =0;
}

void Parser::commit(){

}

void Parser::open(Message* msg){
	mmesg = msg;
	mlist.clear();
	moffset =0;
}
