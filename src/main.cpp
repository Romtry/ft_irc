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
	const unsigned short port = std::atoi(argv[1]);
	if (port > 64000)
	{
		std::cout << "Invalid port" << std::endl;
		return (1);
	}
	const std::string	pswd = argv[2];
	if (pswd.size() > 15)
	{
		std::cout << "Password too long, 15char max !" << std::endl;
		return (1);
	}

	try
	{
		ircserv	test(port, pswd);
		test.Start();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}
