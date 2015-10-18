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

void Parser::putInt(int & data){
	putData(&data, sizeof(int));
}

void Parser::putFloat(float & data){
	putData(&data, sizeof(float));
}


int Parser::getInt(){
	int res;
	getData(&res,sizeof(float));
	return res;
}

float Parser::getFloat(){
	float res;
	getData(&res,sizeof(int));
	return res;
}

void Parser::putData(void* data, int nb){
	ParsingObject structData;
	structData.ptr = data;
	structData.nb = nb;
	mlist.push_front(structData);
}

void Parser::getData(void* data, int len){
	void* datacopy = mmesg->getData();
	memcpy(data,datacopy+moffset,len);
	moffset += len;
}


void Parser::commit(){
	uint8_t lenghtdata =0;//taille totale des donnees a commit contenues dans la liste.
	uint8_t lenghtonedata =0;//taille d'une donnee de la liste

	std::list<ParsingObject>::const_iterator iterator;

	for (iterator = mlist.begin(); iterator != mlist.end(); ++iterator) {
		lenghtdata += iterator->nb;
	}
	mmesg->setDlc(lenghtdata);
	mmesg->startDataAlloc();//alloc d'un nouveau msg
	uint8_t* rawListData = mmesg->getData();

	for (iterator = mlist.begin(); iterator != mlist.end(); ++iterator) {

		memcpy((void*)(rawListData+lenghtonedata), iterator->ptr,iterator->nb);
		lenghtonedata +=iterator->nb;
		//On rentre toutes les data contenues dans la liste dans le nouveau msg.
	}
}

void Parser::rewind(){
	moffset =0;
}

void Parser::open(Message* msg){
	mmesg = msg;
	mlist.clear();
	moffset =0;
}
