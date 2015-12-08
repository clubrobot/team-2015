/*
 * main.cpp
 *
 *  Created on: 1 oct. 2015
 *      Author: ethel
 */

#include <iostream>
#include "../Message.h"
#include "../Log/Color.h"
#include "../Log/logstdout.h"
#include "../Log/olog.h"



using namespace std;

int main(int argc, char **argv) {

	// BUILD MESSAGE

//	int inb1	= 12; // 'i' stands for 'input'
//	int inb2	= 5;
//	float ifl1	= 3.2;
//
//	Message imsg;
//	imsg.append< int >( inb1 );
//	imsg.append( inb2 ); // Also works if omitting the template parameter
//	imsg.append( ifl1 ); // Automatically detect the type of the variable
//
//	// COMPUTE DATA
//
//	size_t length = imsg.getRawDataLength();
//	uint8_t* data = new uint8_t[ length ];
//	imsg.getRawData( data );
//
//	// READ MESSAGE
//
//	Message omsg( data, length ); // 'o' stands for 'output'
//	int onb1 = omsg.retrieve< int >(); // The type must be passed here
//	int onb2 = omsg.retrieve< int >();
//	float ofl1 = omsg.retrieve< float >();
//
//	// CHECK
//
//	cout << inb1 << " =? " << onb1 << endl;
//	cout << inb2 << " =? " << onb2 << endl;
//	cout << ifl1 << " =? " << ofl1 << endl;
//
//	delete[] data;
//	return 0;
LogMessage message;
message.memitter = 5;
message.minformation = "lolilol";
Tag tag = WARNING;
message.mtag = tag;

logstdout out;
out.append(message);

}



