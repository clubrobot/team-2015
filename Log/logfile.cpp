/*
 * logfile.cpp
 *
 *  Created on: 26 nov. 2015
 *      Author: ethel
 */

#include "logfile.h"

//open a logfile specified by its name.
LogFile::LogFile(char *f){
	std::size_t length=filename.copy(f,30,0);
	f[length]='\0';
	file=new std::ofstream;
	file->open(f);
	if (file->fail())
	{
		std::cerr <<"Can't open " << filename << std::endl;
		exit(1);
	}

}

void LogFile::append(const NvjLogSeverity& l, const std::string& m,
		const std::string& details) {
	if (file!=NULL)
		(*file) << m << std::endl;
}

