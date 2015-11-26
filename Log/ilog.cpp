/*
 * ilog.cpp
 *
 *  Created on: Nov 12, 2015
 *      Author: gabriel
 */

#include "ilog.h"

ilog::ilog() {
	// TODO Auto-generated constructor stub

}

ilog::~ilog() {
	// TODO Auto-generated destructor stub
}

void ilog::readFile(const char* filename,char delemiter){
	std::ifstream file(filename);
	std::istream_iterator<char> it(file);

	const int n = 60;
	char *buffer = new char[n];

	file.seekg(ios_base::beg);
	file.get(buffer, n, delemiter);

	while (!file.eof()) {
		std::cout << buffer << std::endl;
		it++;
		file.get(buffer, n, delemiter);
	}
	file.close();
}

int ilog::getlenght(const char* filename) {
	std::ifstream ifile(filename);
	int length;
	ifile.seekg(0,ios_base::end);
	length = ifile.tellg();
	return length;
}
