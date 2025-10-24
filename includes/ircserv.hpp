//
// Created by rothiery on 10/22/25.
//

#pragma once

#include <iostream>
#include <vector>
#include <poll.h>
#include <exception>
#include <netinet/in.h>
// #include <sys/socket.h>

class ircserv
{
	public:
		ircserv(const unsigned int port, const std::string &password);
		void Start();
		void AddClient();
		void Message(unsigned int i);

	private:
		const unsigned int			_port;
		const std::string			_password;
		std::vector<pollfd>			_socket;
};
