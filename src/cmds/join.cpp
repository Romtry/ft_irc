/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdedola <rdedola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 14:26:31 by rdedola           #+#    #+#             */
/*   Updated: 2025/10/30 14:55:48 by rdedola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Channel.hpp"
#include "../../includes/IRCServ.hpp"

void	IRCServ::CMDjoin(Client *client, const std::string &buffer)
{
	if (!client->getIsRegister())
	{
		client->sendMessage(ERR_NOTREGISTERED);
		return;
	}
	std::string channelName = buffer.substr(0, buffer.find_first_of(' '));
	if (channelName[0] != '#' || !channelName[1])
		return;
	channelName.erase(0, 1);
	for (unsigned int i = 0; i < client->getChannels().size(); ++i)
	{
		if (client->getChannels()[i]->getChanName() == channelName)
		{
			 return;
		}
	}
	for (unsigned int i = 0; i < _channels.size(); ++i)
	{
		if (_channels[i]->getChanName() == channelName)
		{
			if (!_channels[i]->getInvite_only() && (_channels[i]->getLimite() == 0 || _channels[i]->getLimite() > _channels[i]->getClients().size()))
			{
				client->addChannel(_channels[i]);
				_channels[i]->addMember(client);
			}
			return;
		}
	}
	Channel *tmp = new Channel(client, channelName);
	tmp->addMember(client);
	client->addChannel(tmp);
	_channels.push_back(tmp);
}
