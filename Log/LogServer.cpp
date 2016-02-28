/*
 * LogServer.cpp
 *
 *  Created on: 23 févr. 2016
 *      Author: gab
 */

#include "LogServer.h"

LogServer::LogServer() : TCPServer(),
	minfo(nullptr), mbufinfo(nullptr),
	mdebug(nullptr), mbufdebug(nullptr),
	mwarning(nullptr), mbufwarning(nullptr),
	merr(nullptr), mbuferr(nullptr)
{
	mbufinfo = new TCPstreambuf(*this, TCPstreambuf::INFO);
	minfo.rdbuf(mbufinfo);
	mbuferr = new TCPstreambuf(*this, TCPstreambuf::ERROR);
	merr.rdbuf(mbuferr);
	mbufwarning = new TCPstreambuf(*this, TCPstreambuf::WARNING);
	mwarning.rdbuf(mbufwarning);
	mbufdebug = new TCPstreambuf(*this, TCPstreambuf::DEBUG);
	mdebug.rdbuf(mbufdebug);
}

LogServer::~LogServer() {
	delete(mbufinfo);
	delete(mbuferr);
	delete(mbufdebug);
	delete(mbufwarning);
}
