//
// Created by rothiery on 10/22/25.
//

#include "ircserv.hpp"
#include <poll.h>

ircserv::ircserv(const unsigned int port, const std::string &password)
	:	_port(port), _password(password)
{
	// ? crée un canal de communication
	// ? AF_INET defini que l'ip est IPv4
	// ? SOCK_STREAM = TCP = handshake = verif lent mais sûr / alternative UDP = pas de verif mais rapide plus d'infos pas sures ex jeux videos
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	// ? defini que la socket est pour un serv avec addresses, ports et paramètres du serv
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(_port);
	// ? accepte toutes les ip
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	// ? envoie le serv "en ligne" -1 si ip deja occupé 0 si le serv a bien loué l'ip / port
	// ! ajouter message erreur en cas de ip / port deja utilisés
	bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

	// ? ajoute la capaciter a recevoir des "demandes" (des clients)
	listen(serverSocket, 15);

	// ? maintenant en attente qu'un client se connect crée une socket par client (les clients ont leur propre socket et ces 2 sockets font le lien)
	// ! ajouter un poll ? pour attendre les nouveaux clients
	pollfd fds;
	fds.fd
	int clientSocket = accept(serverSocket, NULL, NULL);

	char buffer[1024] = {0};
	// ? afficher les messages du client
	while (true)
	{
		recv(clientSocket, buffer, sizeof(buffer), 0);
		std::cout << "Message from client: " << buffer << std::endl;
	}
}
