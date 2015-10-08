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
#define TAILLEMAX_DATA 255 //todo faire allocation memoire a la place
#define TAILLEMAX_TRAME TAILLEMAX_DATA+4

class Message {
public:
	Message();
	virtual ~Message();



	int getRawDataSize();
	void convertToRawData(uint8_t* data);
	int appendRawData(uint8_t* data, int len);

	bool isComplete();

	uint8_t getChecksum() const {
		return mchecksum;
	}

	uint8_t* getData() const {
		return mdata;
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

private:
	int moffset;
protected:

	uint8_t mstart; //octet de start = 0x55
	uint8_t mdestination;//adresse de destination
	uint8_t memitter; //adresse d'envoi
	uint8_t mdlc;//dlc: data length code taille des donnees (de 0 a 8 octets inclus)
    uint8_t* mdata;
	uint8_t mchecksum;
	uint8_t mstop; //octet de stop = 0xAA

};

#endif /* MESSAGE_H_ */
