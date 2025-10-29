//
// Created by rothiery on 10/22/25.
//

#include "../includes/IRCServ.hpp"

IRCServ::IRCServ(const unsigned int port, const std::string &password)
	:	_port(port), _password(password), _socket(0)
{
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
	while (true)
	{
		if (poll(_socket.data(), _socket.size(), 0) == -1)
			throw std::runtime_error("Poll error");
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
		return;
	}
	std::string tmp = buffer;
	parseCommand(i - 1, tmp);
}
