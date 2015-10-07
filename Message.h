/*
 * Message.h
 *
 *  Created on: 1 oct. 2015
 *      Author: ethel
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <stdint.h>
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

	/*compress(Message *msg)
	 * Cette fonction permet de creer une trame de taille optimisee par rapport au nombre
	 * de données que l'on souhaite envoyer.*/
	void compress(Message *msg);

	/*send(Message *msg)
	 *cette fonction prend un objet message
	 *et la transforme en tableau pour pouvoir ensuite être
	 *traitée*/
	void send(Message *msg);

	/*receive(Message *msg)
	 * Cette fonction va stocker dans un tableau "TRAME" les données arrivant par le buffer
	 */
	void receive();

	/* UART_print(Message *msg)
	 * Cette fonction affichera le message sur la sortie standard,
	 * utile pour le debug.
	 */
	void print(Message *msg);

	void traitement();

	void stockerDatas(Message *msg);

	uint8_t checksum(uint8_t tab[TAILLEMAX_TRAME]);
	int recopie();

	void set_emitter();
	void set_slot();
	int set_datas(uint8_t datas);


private:
protected:

	uint8_t mstart; //octet de start = 0x55
	uint8_t mslot_adress;//adresse de destination
	uint8_t memitter; //adresse d'envoi
	uint8_t mdlc;//dlc: data length code taille des donnees (de 0 a 8 octets inclus)
	uint8_t* mdatas;
	uint8_t mchecksum;
	uint8_t mstop; //octet de stop = 0xAA
};

#endif /* MESSAGE_H_ */
