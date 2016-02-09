/*
 * Asservissement.cpp
 *
 *  Created on: 4 févr. 2016
 *      Author: ethel
 */

#include "Asservissement.h"

Asservissement::Asservissement(uint8_t address, TCPClient& client) :
Module(address,client){
}

Asservissement::~Asservissement() {
	// TODO Auto-generated destructor stub
}

bool Asservissement::getCodeur(uint32_t &left, uint32_t &right) {
	Message out;

	out.setEmitter( 0 );
	out.setReceiver( getAddress() );
	out.append< uint8_t >( getcodeur );

	Message in;

	if(requestSlot(out,in)){

		left = in.retrieve<uint32_t>();
		right = in.retrieve<uint32_t>();
		return true;
	}
	return false;
}

bool Asservissement::setCodeur(uint32_t left, uint32_t right){
	Message out, in;
	out.setEmitter( 0 );
	out.setReceiver( getAddress() );
	out.append< uint8_t >( setcodeur );
	out.append< uint32_t >( left );
	out.append< uint32_t >( right );

	return requestSlot(out,in);

}

void Asservissement::run() {
	Clock clk;
	clk.tic();
	//insert anything you want
	wait(1000-clk.tac());

}

bool Asservissement::setPWM(uint16_t leftPWM, uint16_t rightPWM){
	Message out, in;
	out.setEmitter( 0 );
	out.setReceiver( getAddress() );
	out.append< uint8_t >( setpwm );
	out.append< uint32_t >( leftPWM );
	out.append< uint32_t >( rightPWM );

	return requestSlot(out,in);
}


