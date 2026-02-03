/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 09:58:02 by rothiery          #+#    #+#             */
/*   Updated: 2026/02/02 09:58:04 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRCServ.hpp"

void IRCServ::CMDprivmsg(const Client *client, std::string &buffer) const
{
	if (!client->getIsRegister())
	{
		client->sendMessage(ERR_NOTREGISTERED);
		return;
	}
	if (buffer[0] == '#')
	{
		std::string channelName = buffer.substr(0, buffer.find_first_of(' '));
		if (channelName[0] != '#' || !channelName[1])
			return;
		channelName.erase(0, 1);
		for (unsigned int i = 0; i < client->getChannels().size(); ++i)
		{
			if (client->getChannels()[i]->getChanName() == channelName)
			{
				buffer.erase(0, buffer.find_first_of(' '));
				buffer.erase(0, buffer.find_first_not_of(' '));
				for (unsigned int j = 0; j < client->getChannels()[i]->getClients().size(); ++j)
				{
					if (client->getChannels()[i]->getClients()[j]->getNick() != client->getNick())
						client->getChannels()[i]->getClients()[j]->sendMessage(buffer);
				}
				return;
			}
		}
		client->sendMessage(ERR_NOSUCHCHANNEL(channelName));
	}
	else
	{
		std::string nickname = buffer.substr(0, buffer.find_first_of(' '));
		for (unsigned int i = 0; i < _clients.size(); ++i)
		{
			if (nickname == _clients[i]->getNick())
			{
				buffer.erase(0, buffer.find_first_of(' '));
				buffer.erase(0, buffer.find_first_not_of(' '));
				_clients[i]->sendMessage(buffer);
				return;
			}
		}
		client->sendMessage(ERR_NOSUCHCHANNEL(nickname));
	}
}
