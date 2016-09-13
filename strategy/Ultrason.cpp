/*
 * Ultrason.cpp
 *
 *  Created on: 6 mai 2016
 *      Author: ethel
 */

#include "Ultrason.h"


const uint8_t Ultrason::order_stop = 's';
const uint8_t Ultrason::order_disable = 'd';
const uint8_t Ultrason::order_enable = 'e';


Ultrason::Ultrason( uint8_t address, TCPClient& client): Module(address, client) {
	// TODO Auto-generated constructor stub
	startReceiving();

}

Ultrason::~Ultrason() {
	// TODO Auto-generated destructor stub
}


void Ultrason::run(){

	uint8_t* data;
	//data[0]
	uint8_t id, length;

	wait();

	//2 octets quel capteur et quelle distance en cm.
	getBufferData(data, 2);
	id=data[0];
	length=data[1];

	dispatchEvent("data", EventParams() << uint8_t( id), uint8_t( length ));

}


void Ultrason::disableUltrason(){
	stopReceiving();
	morder = DISABLE;
}

void Ultrason::enableUltrason(){
	startReceiving();
	morder = ENABLE;
}


