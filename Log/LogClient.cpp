/*
 * LogClient.cpp
 *
 *  Created on: 23 févr. 2016
 *      Author: gab
 */

#include "LogClient.h"

const Color::Code LogClient::color[4] = {Color::FG_BLUE, Color::FG_GREEN, Color::FG_YELLOW, Color::FG_RED};

LogClient::LogClient() {
	setEvents(this);
}

LogClient::~LogClient() {
}

void LogClient::onConnected(TCPClient* client) {
	std::cout << Color(Color::FG_DEFAULT) << "Connection to log server succeeded" << std::endl;
}

void LogClient::onConnectionFailed(TCPClient* client) {
	std::cout << Color(Color::FG_DEFAULT) << "Connection to log server failed" << std::endl;
}

void LogClient::onDisconnected(TCPClient* client) {
	std::cout << Color(Color::FG_DEFAULT) << "Disconnected from log server" << std::endl;
}

void LogClient::onMessageReceived(TCPClient* client, uint8_t buffer[],
		uint32_t len) {
	std::cout << Color(color[buffer[0]-'A']) << buffer+1 << std::endl;
}
