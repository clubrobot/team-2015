/*
 * main.cpp
 *
 *  Created on: 1 oct. 2015
 *      Author: ethel
 */

#include <iostream>
#include "../Message.h"
#include "../Log/Color.h"




using namespace std;

int main(int argc, char **argv) {

	// BUILD MESSAGE

	int inb1	= 12; // 'i' stands for 'input'
	int inb2	= 5;
	float ifl1	= 3.2;

	Message imsg;
//	imsg.append< int >( inb1 );
//	imsg.append( inb2 ); // Also works if omitting the template parameter
//	imsg.append( ifl1 ); // Automatically detect the type of the variable
	imsg << inb1 << inb2 << ifl1; // Alternative syntax: this is pure awesomeness!! #awesomeness

	// COMPUTE DATA

	size_t length = imsg.getRawDataLength();
	uint8_t* data = new uint8_t[ length ];
	imsg.getRawData( data );

	// READ MESSAGE

	Message omsg( data, length ); // 'o' stands for 'output'
//	int onb1 = omsg.retrieve< int >(); // The type must be passed here
//	int onb2 = omsg.retrieve< int >();
//	float ofl1 = omsg.retrieve< float >();
	int onb1;
	int onb2;
	float ofl1;
	omsg >> onb1 >> onb2 >> ofl1; // #seeabove #awesomeness

	// CHECK

	cout << inb1 << " =? " << onb1 << endl;
	cout << inb2 << " =? " << onb2 << endl;
	cout << ifl1 << " =? " << ofl1 << endl;

	delete[] data;
	return 0;


}



