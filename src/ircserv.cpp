//
// Created by rothiery on 10/22/25.
//

#include "../includes/ircserv.hpp"

// ? init du serv
ircserv::ircserv(const unsigned int port, const std::string &password)
	:	_port(port), _password(password), _sockets(0)
{
	// ? crée un canal de communication
	// ? AF_INET defini que l'ip est IPv4
	// ? SOCK_STREAM = TCP = handshake = verif lent mais sûr / alternative UDP = pas de verif mais rapide plus d'infos pas sures ex jeux videos
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	// ? defini que le socket est pour un serv avec addresses, ports et paramètres du serv
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(_port);
	// ? accepte toutes les ip
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	// ? envoie le serv "en ligne" -1 si ip deja occupé 0 si le serv a bien loué l'ip / port
	if (!bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)));
		throw std::runtime_error("Port already used");


	// ? ajoute la capaciter à recevoir des "demandes" (des clients)
	listen(serverSocket, 15);

	// ? poll sert a capter les demandes
	pollfd servfds;
	// ? stock le socket du serv
	servfds.fd = serverSocket;
	// ? quel event active revent
	servfds.events = POLLIN;
	// ? quand event recoit un message revent s'active
	servfds.revents = 0;
	_socket.push_back(servfds);
}

// ? accepte les clients / affiche les messages
void ircserv::Start()
{
	char buffer[1024] = {0};
	while (true)
	{
		// ? stop jusqu'à ce qu'un message est recu (server comme client) met le revent du socket a 1
		if (!poll(_socket.data(), _socket.size(), 0))
			throw std::runtime_error("Poll error");
		// ? parcourt les sockets
		for (unsigned int i = 0; i < _socket.size(); ++i)
		{
			// ? trouve le socket avec revent 1
			if (_socket[i].revents != 0)
			{
				// ? si index du socket == 0, c'est le serv donc une demande pour rejoindre
				if (i == 0)
					AddClient();
				// ? si index du socket != 0 alors c'est un message d'un client
				else

			}
		}
		// recv(clientSocket, buffer, sizeof(buffer), 0);
		// std::cout << "Message from client: " << buffer << std::endl;
	}
	std::cout << "Server end" << std::endl;
}

// ? ajoute un client aux clients
// ! ajouter message de bienvenue / messages d'arrivé
void ircserv::AddClient()
{
	int clientSocket = accept(_socket[0].fd, NULL, NULL);

	pollfd clientfds;

	clientfds.fd = clientSocket;
	clientfds.events = POLLIN;
	clientfds.revents = 0;
	_socket.push_back(clientfds);
}

// ?