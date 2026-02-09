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
				if (client->getChannels()[i]->isMemmber(client))
				{
					client->sendMessage(RPL_KICK(client->getNick(), nick, channelName, "got kicked"));
					client->getChannels()[i]->removeMember(client);
					ActuChan(client->getChannels()[i], client, i);
				}
			}
			else
				client->sendMessage(ERR_CHANOPRIVSNEEDED(client->getChannels()[i]->getChanName()));
			return;
		}
	}
}
