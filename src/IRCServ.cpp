/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdedola <rdedola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:28:01 by rdedola           #+#    #+#             */
/*   Updated: 2025/10/30 15:18:57 by rdedola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/IRCServ.hpp"

#include <csignal>

bool isrunning = true;

static void interrupt_handler(int signum)
{
	(void)signum;
	isrunning = false;
}

IRCServ::IRCServ(const unsigned int port, const std::string &password)
	:	_port(port), _password(password), _socket(0)
{
	signal(SIGINT, interrupt_handler);
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(_port);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
	{
		throw std::runtime_error("Port already used");
	}


	listen(serverSocket, 15);

	pollfd servfds;
	servfds.fd = serverSocket;
	servfds.events = POLLIN;
	servfds.revents = 0;
	_socket.push_back(servfds);
}

IRCServ::~IRCServ()
{
	while (!_clients.empty())
	{
		while (!_clients[0]->getChannels().empty())
		{
			_clients[0]->getChannels()[0]->removeMember(_clients[0]);
			ActuChan(_clients[0]->getChannels()[0], _clients[0], 0);
		}
		close(_clients[0]->getClientSocket());
		const Client *tmp = _clients[0];
		_clients.erase(_clients.begin());
		delete (tmp);
	}
	close(_socket[0].fd);
}

// ! ajouter password
// ! hexchat working
void IRCServ::Start()
{
	std::cout << "\e[33m██╗██████╗  ██████╗    ███████╗███████╗██████╗ ██╗   ██╗" RESET << std::endl;
	std::cout << "\e[33m██║██╔══██╗██╔════╝    ██╔════╝██╔════╝██╔══██╗██║   ██║" RESET << std::endl;
	std::cout << "\e[33m██║██████╔╝██║         ███████╗█████╗  ██████╔╝██║   ██║" RESET << std::endl;
	std::cout << "\e[33m██║██╔══██╗██║         ╚════██║██╔══╝  ██╔══██╗╚██╗ ██╔╝" RESET << std::endl;
	std::cout << "\e[33m██║██║  ██║╚██████╗    ███████║███████╗██║  ██║ ╚████╔╝ " RESET << std::endl;
	std::cout << "\e[33m╚═╝╚═╝  ╚═╝ ╚═════╝    ╚══════╝╚══════╝╚═╝  ╚═╝  ╚═══╝  " RESET << std::endl;
	while (isrunning)
	{
		if (poll(_socket.data(), _socket.size(), 0) == -1)
		{
			if (isrunning)
				std::runtime_error("Poll error");
			return;
		}
		for (unsigned int i = 0; i < _socket.size(); ++i)
		{
			if (_socket[i].revents != 0)
			{
				if (i == 0)
					AddClient();
				else
					Message(i);
			}
		}
	}
	std::cout << "Server end" << std::endl;
}

// ! ajouter message de bienvenue / messages d'arrivé
void IRCServ::AddClient()
{
	int clientSocket = accept(_socket[0].fd, NULL, NULL);

	pollfd clientfds;

	clientfds.fd = clientSocket;
	clientfds.events = POLLIN;
	clientfds.revents = 0;
	_socket.push_back(clientfds);
	Client *temp = new Client(clientSocket);
	_clients.push_back(temp);
	std::cout << "CLIENT HAS JOIN" << std::endl;
}

void IRCServ::Message(const unsigned int i)
{
	char buffer[1024] = {0};
	unsigned int size = recv(_socket[i].fd, buffer, sizeof(buffer), 0);
	if (size == 0)
	{
		std::cout << "User disconnected" << std::endl;
		close (_socket[i].fd);
		_socket.erase(_socket.begin() + i);
		while (!_clients[i - 1]->getChannels().empty())
		{
			_clients[i - 1]->getChannels()[0]->removeMember(_clients[i - 1]);
			ActuChan(_clients[i - 1]->getChannels()[0], _clients[i - 1], 0);
		}
		Client *tmp = _clients[i - 1];
		_clients.erase(_clients.begin() + i - 1);
		delete (tmp);
		return;
	}
	std::string tmp = buffer;
	parseCommand(_clients[i - 1], tmp);
}

void IRCServ::ActuChan(const Channel *channel, Client *client, const unsigned int index_chan)
{
	if (channel->getClients().empty())
	{
		for (unsigned int i = 0; i < _channels.size(); ++i)
		{
			if (_channels[i] == channel)
			{
				Channel *tmp = _channels[i];
				_channels.erase(_channels.begin() + i);
				delete (tmp);
			}
		}
	}
	client->getChannels().erase(client->getChannels().begin() + index_chan);
}
