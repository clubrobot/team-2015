/*
 * LogStream.cpp
 *
 *  Created on: 23 févr. 2016
 *      Author: ethel
 */

#include "LogStream.h"

LogStream::LogStream(): std::ostream(){

}

LogStream::LogStream(TCPstreambuf& buff): std::ostream() {

this->rdbuf(&buff);

}

LogStream::~LogStream() {
}

LogStream& operator<<(LogStream& ofs, int channel){
	ofs << channel << " " << ofs;
	return ofs;
}
