/*
 * Power.cpp
 *
 *  Created on: 4 févr. 2016
 *      Author: ethel
 */

#include "Power.h"

Power::Power(uint8_t address, TCPClient& client) : Module(address,client) {
	// TODO Auto-generated constructor stub

}

Power::~Power() {
	// TODO Auto-generated destructor stub
}

bool Power::getBattery(uint16_t &level){
	Message out;

	out.setEmitter( 0 );
	out.setReceiver( 0 );
	out.append< uint8_t >( 4 );

	Message in;

	if(requestBoard(out,in)){

		level = in.retrieve<uint16_t>();
		return true;
	}
	return false;
}


uint32_t Power::estimateAutonomy(){
	uint32_t autonomy;
	uint16_t level;
	getBattery(level);

	//algo very hard ODE !!! Jean-Louis Merien
	autonomy = 10000*level; //todo :edit and find better
	return autonomy;
}
