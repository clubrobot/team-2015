/*
 * logfile.cpp
 *
 *  Created on: 26 nov. 2015
 *      Author: ethel
 */

#include "logfile.h"

////open a logfile specified by its name.
LogFile::LogFile(char *f){

	filename = f;
	file=new std::ofstream;
	file->open(f,std::ios_base::app);

	if (file->fail())
	{
		std::cerr <<"Can't open " << filename << std::endl;
		exit(1);
	}

}

void LogFile::append(LogMessage message) {

	if (file!=NULL){
		std::string info = message.getInformation();
		(*file) << info << std::endl;//on recupere que l'info
	}
}

