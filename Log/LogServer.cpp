/*
 * LogServer.cpp
 *
 *  Created on: 23 févr. 2016
 *      Author: gab
 */

#include "LogServer.h"

LogServer::LogServer() : TCPServer(), minfo(mbuf), mbuf(*this){
	this->launch(3003,1);


}

LogServer::~LogServer() {
}
