/*
 * LogStream.h
 *
 *  Created on: 23 févr. 2016
 *      Author: ethel
 */

#ifndef LOGSTREAM_H_
#define LOGSTREAM_H_

#include <ostream>
#include <streambuf>
#include "TCPstreambuf.h"



class LogStream : public std::ostream {
public:

	LogStream();
	LogStream(TCPstreambuf& buf);
	virtual ~LogStream();

	friend LogStream& operator<<(LogStream& ofs, int channel);

};

#endif /* LOGSTREAM_H_ */
