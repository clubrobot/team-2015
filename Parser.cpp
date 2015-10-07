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
	objectList structData;
	int* ptrdata = nullptr;
	*ptrdata = data;
	structData.ptr = ptrdata;
	structData.nb = sizeof(*ptrdata);
	mlist.push_front(structData);
}

void Parser::putFloat(float data){
	objectList structData;
	int* ptrdata = nullptr;
	*ptrdata = data;
	structData.ptr = ptrdata;
	structData.nb = sizeof(*ptrdata);
	mlist.push_front(structData);
}

//
//int Parser::getInt(){
//
//}
//float Parser::getFloat(){
//
//}

//void Parser::putData(const void* data, int nb){
//	objectList structData;
//	void* ptrcopy = nullptr;
//	*ptrcopy = &data;
//	structData.ptr = ptrcopy;
//	structData.nb = nb;
//	mlist.push_front(structData);
//}

void Parser::getData(void*, int){

}
void Parser::commit(){

}
void Parser::open(Message* msg){

}
