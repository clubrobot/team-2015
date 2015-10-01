/*
 * Message.cpp
 *
 *  Created on: 1 oct. 2015
 *      Author: ethel
 */

#include "Message.h"


Message::Message() {

	// TODO Auto-generated constructor stub
	mstart =0x55;
	mslot_adress=0;
	memitter=0;
	mdlc=0;
	mdatas[TAILLEMAX_DATA]= {};
	mchecksum=0;
	mstop = 0xAA;

}

Message::~Message() {
	// TODO Auto-generated destructor stub
}


uint8_t Message::checksum(uint8_t tab[TAILLEMAX_TRAME]){
	int i;
	uint8_t somme;
	for (i = 0; i < tab[2]; i++) {
		somme += tab[3 + i];
	}
	return somme;
}


