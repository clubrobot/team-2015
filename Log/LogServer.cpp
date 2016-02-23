/*
 * LogServer.cpp
 *
 *  Created on: 23 févr. 2016
 *      Author: gab
 */

#include "LogServer.h"

LogServer::LogServer() : TCPServer(), mbuf(this) {
}

LogServer::~LogServer() {
}
