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
	if(!file->is_open()){
		file->open(filename.c_str(),std::ios_base::app);
	}
	if (file!=NULL){
		(*file) << message.getStringFromTag() << ":";//add delemiter
		(*file) << message.getTime() << ":";
		(*file) << message.getEmitter() << ":";
		(*file) << message.getInformation() << std::endl;
	}
	file->close();
}

