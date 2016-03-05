/*
 * LogServer.cpp
 *
 *  Created on: 23 févr. 2016
 *      Author: gab
 */

#include "LogServer.h"

LogServer::LogServer() : TCPServer(),
	info(nullptr),
	debug(nullptr),
	warning(nullptr),
	error(nullptr),
	mbufinfo(nullptr),
	mbufdebug(nullptr),
	mbufwarning(nullptr),
	mbuferr(nullptr)
{
	mbufinfo = new TCPstreambuf(*this, TCPstreambuf::INFO);
	info.rdbuf(mbufinfo);
	mbuferr = new TCPstreambuf(*this, TCPstreambuf::ERROR);
	error.rdbuf(mbuferr);
	mbufwarning = new TCPstreambuf(*this, TCPstreambuf::WARNING);
	warning.rdbuf(mbufwarning);
	mbufdebug = new TCPstreambuf(*this, TCPstreambuf::DEBUG);
	debug.rdbuf(mbufdebug);
}

LogServer::~LogServer() {
	delete(mbufinfo);
	delete(mbuferr);
	delete(mbufdebug);
	delete(mbufwarning);
}
