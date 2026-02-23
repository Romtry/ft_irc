/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:46:18 by rothiery          #+#    #+#             */
/*   Updated: 2026/01/22 11:46:21 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/IRCServ.hpp"

void IRCServ::CMDkick(Client *client, std::string &buffer)
{
	if (!client->getIsRegister())
	{
		client->sendMessage(ERR_NOTREGISTERED);
		return;
	}
	std::string channelName = buffer.substr(0, buffer.find_first_of(' '));
	if (channelName[0] != '#' || !channelName[1])
		return;
	buffer.erase(0, buffer.find_first_of(' '));
	buffer.erase(0, buffer.find_first_not_of(' '));
	const std::string nick = buffer.substr(0, buffer.find_first_of(' '));
	buffer.erase(0, buffer.find_first_of(' '));
	buffer.erase(0, buffer.find_first_not_of(' '));
	for (unsigned int i = 0; i < client->getChannels().size(); ++i)
	{
		if (channelName == client->getChannels()[i]->getChanName())
		{
			if (client->getChannels()[i]->getOperator(client))
			{
				for (unsigned int j = 0; j < client->getChannels()[i]->getClients().size(); ++j)
				{
					if (client->getChannels()[i]->getClients()[j]->getNick() == nick)
					{
						client->getChannels()[i]->sendAll(RPL_KICK(client->getNick(), nick, channelName, "got kicked"));
						client->getChannels()[i]->removeMember(client->getChannels()[i]->getClients()[j]);
						ActuChan(client->getChannels()[i], client->getChannels()[i]->getClients()[j], i);
						return;
					}
				}
				client->sendMessage(ERR_NOSUCHNICK(nick));
			}
			else
				client->sendMessage(ERR_CHANOPRIVSNEEDED(client->getChannels()[i]->getChanName()));
			return;
		}
	}
}
