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
	mdestination=0;
	memitter=0;
	mdlc=0;
	mdata = nullptr;
	mchecksum=0;
	mstop = 0xAA;

	moffset = 0;

}

Message::~Message() {
	// TODO Auto-generated destructor stub
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

int Message::appendRawData(uint8_t* data, int len) {
	int res = getRawDataSize() - (moffset + len);

	// TODO : Finish that

	if(res < 0) {
		moffset = getRawDataSize();
	}
	else {
		moffset += len;
	}

	return res;
}

bool Message::isComplete() {
	return mdata != nullptr && moffset == getRawDataSize();
}
