/*
 * Message.cpp
 *
 *  Created on: 1 oct. 2015
 *      Author: ethel
 */

#include "Message.h"


Message::Message() {
	mstart = START;
	mdestination=0;
	memitter=0;
	mdlc=0;
	mdata = nullptr;
	mchecksum=0;
	mstop = STOP;
}

Message::~Message() {
	if(mdata) stopDataAlloc();
}

//uint8_t Message::checksum(uint8_t tab[TAILLEMAX_TRAME]){
//	int i;
//	uint8_t somme;
//	for (i = 0; i < tab[2]; i++) {
//		somme += tab[3 + i];
//	}
//	return somme;
//}

int Message::getRawDataSize() {
	return mdlc + 6;
}

void Message::convertToRawData(uint8_t* data) {
	if(mdlc != 0 && mdata != nullptr) {
		data[0] = mstart;
		data[1] = mdestination;
		data[2] = memitter;
		data[3] = mdlc;
		memcpy(data, mdata, getRawDataSize());
		data[4+mdlc] = mchecksum;
		data[5+mdlc] = mstop;
	}
}

bool Message::isComplete() {

	//TODO: Verify start/stop/checksum

	return true;
}
