/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdedola <rdedola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 14:26:31 by rdedola           #+#    #+#             */
/*   Updated: 2026/02/04 14:29:44 by rdedola          ###   ########.fr       */
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
	for (unsigned int i = 0; i < client->getChannels().size(); ++i)
	{
		if (client->getChannels()[i]->getChanName() == channelName)
		{
			 return;
		}
	}
	std::cout << "channel size: " << _channels.size() << std::endl;
	if (_channels.size() > 0)
		std::cout << "channel[0]: " << _channels[0]->getChanName() << std::endl;
	for (unsigned int i = 0; i < _channels.size(); ++i)
	{
		if (_channels[i]->getChanName() == channelName)
		{
			if ((_channels[i]->getLimite() == 0 || _channels[i]->getLimite() > _channels[i]->getClients().size()))
			{
				if (!_channels[i]->getInvite_only())
				{
					client->addChannel(_channels[i]);
					_channels[i]->addMember(client);
					client->sendMessage(RAW_JOIN(client->getNick(), client->getUser(), "nanachi", channelName));
					if (!_channels[i]->getTopic().empty())
						client->sendMessage(RAW_TOPIC(client->getNick(), client->getUser(), "nanachi", client->getChannels()[i]->getChanName(), _channels[i]->getTopic()));
					return ;
				}
				else
				{
					for (unsigned int j = 0; j < _channels[i]->getGuests().size(); ++j)
					{
						if (_channels[i]->getGuests()[j] == client)
						{
							client->addChannel(_channels[i]);
							_channels[i]->addMember(client);
							client->sendMessage(RAW_JOIN(client->getNick(), client->getUser(), "nanachi", channelName));
							_channels[i]->getGuests().erase(_channels[i]->getGuests().begin() + j);
							if (!_channels[i]->getTopic().empty())
								client->sendMessage(RAW_TOPIC(client->getNick(), client->getUser(), "nanachi", client->getChannels()[i]->getChanName(), _channels[i]->getTopic()));
							return ;
						}
						else
						{
							client->sendMessage(ERR_INVITEONLYCHAN(client->getNick(), _channels[i]->getChanName()));
						}
					}
				}
			}
			return;
		}
	}
	Channel *tmp = new Channel(client, channelName);
	tmp->addMember(client);
	client->addChannel(tmp);
	client->sendMessage(RAW_JOIN(client->getNick(), client->getUser(), "nanachi", channelName));
	_channels.push_back(tmp);
}
