/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleCommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdedola <rdedola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:27:50 by rdedola           #+#    #+#             */
/*   Updated: 2026/02/04 12:56:53 by rdedola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <variant>

#include "../../includes/defines.hpp"
#include "../../includes/IRCServ.hpp"

void IRCServ::parseCommand(Client *client, const std::string &buffer)
{
	unsigned long i = 0;
	while (buffer[i])
	{
		if (buffer[i] == ' ')
		{
			i = buffer.find('\n') + 1;
			if (buffer.size() == i)
				return;
			continue;
		}
		if (buffer.find(' ', i) == std::string::npos)
			return;
		if (buffer.find(' ', i) > buffer.find('\n', i))
		{
			i = buffer.find('\n') + 1;
			if (buffer.size() == i)
				return;
			continue;
		}
		client->pushbackTocken(buffer.substr(i, buffer.find(' ', i) - i));
		i = buffer.find(' ', i);
		i = buffer.find_first_not_of(' ', i);
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
	if (client->getTokens(0) == "JOIN")
		CMDjoin(client, client->getTokens(1));
	else if (client->getTokens(0) == "NICK")
		CMDnick(client, client->getTokens(1));
	else if (client->getTokens(0) == "PASS")
		CMDpass(client, client->getTokens(1));
	else if (client->getTokens(0) == "USER")
		CMDuser(client);
	else if (client->getTokens(0) == "TOPIC")
		CMDtopic(client, client->getTokens(1));
	else if (client->getTokens(0) == "PART")
		CMDpart(client, client->getTokens(1));
	else if (client->getTokens(0) == "KICK")
		CMDkick(client, client->getTokens(1));
	else if (client->getTokens(0) == "PRIVMSG")
		CMDprivmsg(client, client->getTokens(1));
	else if (client->getTokens(0) == "MODE")
		CMDmode(client, client->getTokens(1));
	else if (client->getTokens(0) != "INVITE")
		CMDinvite(client, client->getTokens(1));
	else if (client->getTokens(0) != "CAP")
		client->sendMessage(ERR_UNKNOWNCOMMAND(client->getTokens(0)));
	// client->printToken();
	// for (unsigned int i = 0; i < client->getChannels().size(); ++i)
	// 	std::cout << "client " << client->getNick() << " channels = " << client->getChannels()[i]->getChanName() << " i: " << i << std::endl;
	if (client->getChannels().empty())
	{
		std::cout << "no more channels" << std::endl;
	}
	else
	{
		for (unsigned int i = 0; i < client->getChannels().size(); ++i)
		{
			std::cout << "chan: " << client->getChannels()[i]->getChanName() << std::endl;
			for (unsigned int j = 0; j < client->getChannels()[i]->getClients().size(); ++j)
			{
				std::cout << "client[" << j << "]: " << client->getChannels()[i]->getClients()[j]->getNick() << std::endl;
			}
		}
	}
	client->clearToken();
}
