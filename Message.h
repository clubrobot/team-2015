/*
 * Message.h
 *
 *  Created on: 1 oct. 2015
 *      Author: ethel
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <stdint.h>
#include <cstring>
#include <arietta-comlib/Serial/UARTServer.h>
#include <vector>

#define START 0x55
#define STOP 0xAA

class Message {
protected:

	uint8_t mstart; //octet de start = 0x55
	uint8_t mdestination;//adresse de destination
	uint8_t memitter; //adresse d'envoi
	uint8_t mdlc;//dlc: data length code taille des donnees (de 0 a 8 octets inclus)
	uint8_t mchecksum;
	uint8_t mstop; //octet de stop = 0xAA
	uint8_t* mdata;

public:
	Message();
	virtual ~Message();

	int getRawDataSize();
	void convertToRawData(uint8_t* data);

	bool isComplete();

	uint8_t getChecksum() const {
		return mchecksum;
	}

	uint8_t* getData() const {
		return mdata;
	}

	void startDataAlloc() {
		mdata = new uint8_t[mdlc];
	}

	void stopDataAlloc() {
		delete(mdata);
		mdata = nullptr;
	}

	uint8_t* getStartAddr() {
		return &mstart;
	}

	uint8_t* getAfterDataAddr() {
		return &mchecksum;
	}

	uint8_t getDestination() const {
		return mdestination;
	}

	uint8_t getDataSize() const {
		return mdlc;
	}

	uint8_t getEmitter() const {
		return memitter;
	}

};

#endif /* MESSAGE_H_ */
