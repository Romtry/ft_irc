/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdedola <rdedola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:28:06 by rdedola           #+#    #+#             */
/*   Updated: 2025/10/30 12:28:19 by rdedola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/IRCServ.hpp"

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
		IRCServ	test(port, pswd);
		test.Start();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}
