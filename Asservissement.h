/*
 * Asservissement.h
 *
 *  Created on: 4 févr. 2016
 *      Author: ethel
 */

#include "Module.h"
#include "Message.h"


#ifndef ASSERVISSEMENT_H_
#define ASSERVISSEMENT_H_

class Asservissement : public Module {
public:
	Asservissement(uint8_t address, TCPClient& client);
	virtual ~Asservissement();

protected:

	void run();
//	uint16_t getCodeur(&int_16 value1, &int_16 value2);
//
	bool setCodeur(uint32_t left, uint32_t right);
	bool getCodeur(uint32_t &left, uint32_t &right);
	bool setPWM(uint16_t leftPWM, uint16_t rightPWM);

	/*getcodeur(&int_16 value1, &int_16 value2 ){
		crée out, in (vide)...
		requestboard(out,&in)
		in on décode : getRawData
		----> et on récup valeur1 et 2. (2 octets par donnée int 16)
	}
*/

private:




};

#endif /* ASSERVISSEMENT_H_ */
