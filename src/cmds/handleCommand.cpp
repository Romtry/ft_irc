/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseCommand.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdedola <rdedola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:27:50 by rdedola           #+#    #+#             */
/*   Updated: 2025/10/30 15:20:08 by rdedola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <variant>

#include "../../includes/defines.hpp"
#include "../../includes/IRCServ.hpp"

void	skipSpaces(const std::string &str, unsigned int &i)
{
	i = str.find_first_not_of(' ', i);
}

void IRCServ::parseCommand(Client *client, const std::string &buffer)
{
	unsigned int i = 0;
	while (buffer[i])
	{
		if (buffer[i] == ' ')
		{
			i = buffer.find('\n') + 1;
			if (buffer.size() == i)
				return;
			continue;
		}
		client->pushbackTocken(buffer.substr(i, buffer.find(' ', i) - i));
		i = buffer.find(' ', i);
		skipSpaces(buffer, i);
		if (buffer[buffer.find('\n', i) - 1] == '\r')
		{
			client->pushbackTocken(buffer.substr(i, buffer.find('\r', i) - i));
			i = buffer.find('\n', i) + 1;
			execCommand(client);
		}
		else
		{
			client->pushbackTocken(buffer.substr(i, buffer.find('\n', i) - i));
			i = buffer.find('\n', i) + 1;
			execCommand(client);
		}
	}
}

void IRCServ::execCommand(Client *client)
{
	// if (client->getTokens(0) == "JOIN")
	// 	CMDjoin(client, client->getTokens(1));
	if (client->getTokens(0) == "NICK")
		CMDnick(client, client->getTokens(1));
	else if (client->getTokens(0) == "PASS")
		CMDpass(client, client->getTokens(1));
	else if (client->getTokens(0) == "USER")
		CMDuser(client, client->getTokens(1));
	else if (client->getTokens(0) != "CAP")
		std::cout << ERR_UNKNOWNCOMMAND(client->getTokens(0)) << std::endl;
	client->printTocken();
	client->clearToken();
}