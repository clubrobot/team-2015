/*
 * main.cpp
 *
 *  Created on: 1 oct. 2015
 *      Author: ethel
 */
#include "../Message.h"
#include "../MessageBuilder.h"
#include "../Parser.h"

int main(int argc, char **argv) {
	int nb1 =12;
	int nb2 =5;
	float fl1 = 3.2;
	Parser parser;
	Message msg;
	parser.open(&msg);
	//	parser.putData(data,12);//Ne fonctionne pas
	parser.putInt(nb1);
	parser.putInt(nb2);
	parser.putFloat(fl1);
	parser.commit();

	return 0;
}



