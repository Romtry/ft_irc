//
// Created by rothiery on 10/22/25.
//

#pragma once

#include <iostream>
#include <vector>
#include <netinet/in.h>
// #include <sys/socket.h>

class ircserv
{
	public:
		ircserv(const unsigned int port, const std::string &password);

	private:
		const unsigned int	_port;
		const std::string	_password;
		std::vector<int>	_clientSock;
};