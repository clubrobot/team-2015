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


void ilog::readFile(const char* filename){
	std::ifstream infile(filename);//chemin ou sauver fichier de log

	std::string ligne;//on lit ligne par ligne

	infile.seekg(std::ios_base::beg);

	while(std::getline(infile,ligne)){
		std::cout << ligne << std::endl;
	}

	infile.close();
}

int ilog::getlenght(const char* filename) {
	std::ifstream ifile(filename);
	int length;
	ifile.seekg(0,ios_base::end);
	length = ifile.tellg();
	return length;
}
