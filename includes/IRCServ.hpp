//
// Created by rothiery on 10/22/25.
//

#pragma once

#include <iostream>
#include <vector>
#include <poll.h>
#include <exception>
#include <netinet/in.h>
#include <cstdlib>
#include <unistd.h>

#include "Client.hpp"

class Client;

class IRCServ
{
	public:
		IRCServ(const unsigned int port, const std::string &password);

		void Start();
		void AddClient();
		void Message(unsigned int i);

		void parseCommand(unsigned int i, std::string &buffer);
		void CMDpass(unsigned int clientindex, std::string &buffer);
		void CMDnick(unsigned int clientindex, std::string &buffer);
		void CMDuser(unsigned int clientindex, std::string &buffer);

	private:
		const unsigned int			_port;
		const std::string			_password;
		std::vector<pollfd>			_socket;
		std::vector<Client *>		_clients;
};
