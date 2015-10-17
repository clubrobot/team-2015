/*
 * MessageBuilder.cpp
 *
 *  Created on: Oct 8, 2015
 *      Author: gabriel
 */

#include "MessageBuilder.h"

MessageBuilder::MessageBuilder() {
	moffset = 0;
	mcollecting = false;
	mmsgqueue = std::queue<Message>();
	mcurrentMsg = Message();
	mlsbyte = 0;
}

MessageBuilder::~MessageBuilder() {
}

void MessageBuilder::appendRawData(uint8_t* data, int len) {
	int counter = len;
	uint8_t* databckup = data;

	//Tant que toute la data n'a pas été traitée
	while(counter > 0) {
		if(!mcollecting) { //Si le message n'est pas commencé
			if(mlsbyte == STOP && data[0] == START) { //Si un message commence
				mcurrentMsg = Message();
				mcollecting = true;
			}
			else { //Si toujours pas de message, on avance la lecture
				data++;
				counter--;
				mlsbyte = data[0];
			}
		}

		// Le message a commencé
		if(mcollecting) {
			int lenghtToCopy = 0, dlc = mcurrentMsg.getDataSize();

			uint8_t* address = nullptr;

			if(dlc != 0 && moffset >= (4 + dlc) ) { // Si on est après la data
				lenghtToCopy = (6 + dlc) - moffset;
				address = mcurrentMsg.getAfterDataAddr();
			}
			else if(moffset >= 4 ) { //Si on est au début de la data
				lenghtToCopy = (4 + dlc) - moffset;
				address = mcurrentMsg.getData();
			}
			else if(moffset >= 0) { //Si on est en début de trame
				lenghtToCopy = 4 - moffset;
				address = mcurrentMsg.getStartAddr();
			}

			lenghtToCopy = (lenghtToCopy < counter) ? lenghtToCopy : counter;

			memcpy(address, data, lenghtToCopy);

			counter -= lenghtToCopy;
			moffset += lenghtToCopy;

			if(moffset == 4) { //DLC reçu
				mcurrentMsg.startDataAlloc(); //On alloue la mémoire pour le tableau
			}

			if(dlc != 0 && moffset == (6 + dlc) ) { //Si le message est fini
				mcollecting = false;
				moffset = 0;
				if(mcurrentMsg.isComplete()) { //Si le message est conforme on l'ajoute à la pile
					mmsgqueue.push(mcurrentMsg);
				}
				else { //Sinon on libère la data
					mcurrentMsg.stopDataAlloc();
				}
			}

		}
	}
	mlsbyte = databckup[len-1];
}

Message MessageBuilder::retrieveMessage() {
	Message res = mmsgqueue.front();
	mmsgqueue.pop();
	return res;
}
