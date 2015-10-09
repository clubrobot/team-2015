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

//
//int Parser::getInt(){
//
//}
//float Parser::getFloat(){
//
//}

void Parser::putData(void* data, int nb){
	ParsingObject structData;
	structData.ptr = data;
	structData.nb = nb;
	mlist.push_front(structData);
}

void Parser::getData(void* data, int nb){
	void* datacopy = mmesg->getData();
	memcpy(data,datacopy,nb);
}

void Parser::commit(){

}
void Parser::open(Message* msg){

}
