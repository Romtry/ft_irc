//
// Created by rothiery on 10/22/25.
//

#include "../includes/ircserv.hpp"

int	main(const int argc, const char **argv)
{
	if (argc != 3)
	{
		std::cout << "./ircserv <port> <password>" << std::endl;
		return (1);
	}
	unsigned short	port = atoi(argv[1]);
	if (!isalnum(port) || port > 64000)
	{
		std::cout << "Invalid port" << std::endl;
		return (1);
	}
	std::string	pswd = argv[2];
	if (sizeof(pswd) > 15)
	{
		std::cout << "Password too long, 15char max !" << std::endl;
	}

	ircserv	test(port, argv[2]);
}
