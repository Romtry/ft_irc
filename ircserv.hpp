//
// Created by rothiery on 10/22/25.
//

#pragma once

#include <iostream>
#include <vector>
#include <netinet/in.h>
// #include <sys/socket.h>

// struct pollfd
// {
// 	int   fd;       // le descripteur de fichier
// 	short events;   // événements que l'on veut surveiller (lecture, écriture, etc.)
// 	short revents;  // événements réellement survenus (rempli par poll)
// };

class ircserv
{
	public:
		ircserv(const unsigned int port, const std::string &password);

	private:
		const unsigned int	_port;
		const std::string	_password;
		std::vector<int>	_clientSock;
};