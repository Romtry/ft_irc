//
// Created by rothiery on 10/22/25.
//

#include "ircserv.hpp"

int	main(const int argc, const char **argv)
{
	if (argc != 3)
	{
		std::cout << "./ircserv <port> <password>" << std::endl;
		return (1);
	}
	// ! port positif & < 64000  unsigned short
	ircserv	test(6667, argv[2]);
}