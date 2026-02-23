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

void	IRCServ::CMDjoin(Client *client, std::string &buffer)
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
	std::string pwd = buffer.substr(0, buffer.find_first_of(' '));
	buffer.erase(0, buffer.find_first_of(' '));
	buffer.erase(0, buffer.find_first_not_of(' '));
	for (unsigned int i = 0; i < client->getChannels().size(); ++i)
	{
		if (client->getChannels()[i]->getChanName() == channelName)
		{
			 return;
		}
	}
	// std::cout << "channel size: " << _channels.size() << std::endl;
	if (_channels.size() > 0)
		// std::cout << "channel[0]: " << _channels[0]->getChanName() << std::endl;
	for (unsigned int i = 0; i < _channels.size(); ++i)
	{
		if (_channels[i]->getChanName() == channelName)
		{
			if ((_channels[i]->getLimite() == 0 || _channels[i]->getLimite() > _channels[i]->getClients().size()))
			{
				if (!_channels[i]->getInvite_only())
				{
					if (_channels[i]->getPassword().empty() || pwd == _channels[i]->getPassword())
					{
						client->addChannel(_channels[i]);
						_channels[i]->addMember(client);
						for (unsigned int k = 0; k < _channels[i]->getClients().size(); ++k)
						{
							if (_channels[i]->getClients()[k] == client)
								continue;
							_channels[i]->getClients()[k]->sendMessage(RAW_JOIN(client->getNick(), client->getUser(), "nanachi", channelName));
						}
						client->sendMessage(RAW_JOIN(client->getNick(), client->getUser(), "nanachi", channelName));
						std::string names;
						for (unsigned int k = 0; k < _channels[i]->getClients().size(); ++k)
						{
							if (k == 0)
							{
								if (_channels[i]->getOperator(_channels[i]->getClients()[k]))
									names += "@" + _channels[i]->getClients()[k]->getNick();
								else
									names += _channels[i]->getClients()[k]->getNick();
							}
							else
							{
								if (_channels[i]->getOperator(_channels[i]->getClients()[k]))
									names += " @" + _channels[i]->getClients()[k]->getNick();
								else
									names += " " + _channels[i]->getClients()[k]->getNick();
							}
						}
						// std::cout << "names: " << names << std::endl;
						client->sendMessage(RPL_NAMREPLY(client->getNick(), _channels[i]->getChanName(), names));
						client->sendMessage(RPL_ENDOFNAMES(client->getNick(), _channels[i]->getChanName()));
						if (!_channels[i]->getTopic().empty())
							client->sendMessage(RAW_TOPIC(client->getNick(), client->getUser(), "nanachi", client->getChannels()[i]->getChanName(), _channels[i]->getTopic()));
						return ;
					}
				}
				for (unsigned int j = 0; j < _channels[i]->getGuests().size(); ++j)
				{
					if (_channels[i]->getGuests()[j] == client)
					{
						if (_channels[i]->getPassword().empty() || pwd == _channels[i]->getPassword())
						{
							client->addChannel(_channels[i]);
							_channels[i]->addMember(client);
							for (unsigned int k = 0; k < _channels[i]->getClients().size(); ++k)
							{
								if (_channels[i]->getClients()[k] == client)
									continue;
								_channels[i]->getClients()[k]->sendMessage(RAW_JOIN(client->getNick(), client->getUser(), "nanachi", channelName));
							}
							client->sendMessage(RAW_JOIN(client->getNick(), client->getUser(), "nanachi", channelName));
							std::string names;
							for (unsigned int k = 0; k < _channels[i]->getClients().size(); ++k)
							{
								if (k == 0)
								{
									if (_channels[i]->getOperator(_channels[i]->getClients()[k]))
										names += "@" + _channels[i]->getClients()[k]->getNick();
									else
										names += _channels[i]->getClients()[k]->getNick();
								}
								else
								{
									if (_channels[i]->getOperator(_channels[i]->getClients()[k]))
										names += " @" + _channels[i]->getClients()[k]->getNick();
									else
										names += " " + _channels[i]->getClients()[k]->getNick();
								}
							}
							// std::cout << "names: " << names << std::endl;
							client->sendMessage(RPL_NAMREPLY(client->getNick(), _channels[i]->getChanName(), names));
							client->sendMessage(RPL_ENDOFNAMES(client->getNick(), _channels[i]->getChanName()));
							_channels[i]->getGuests().erase(_channels[i]->getGuests().begin() + j);
							if (!_channels[i]->getTopic().empty())
								client->sendMessage(RAW_TOPIC(client->getNick(), client->getUser(), "nanachi", client->getChannels()[i]->getChanName(), _channels[i]->getTopic()));
							return ;
						}
					}
					client->sendMessage(ERR_INVITEONLYCHAN(client->getNick(), _channels[i]->getChanName()));
				}
			}
			return;
		}
	}
	Channel *tmp = new Channel(client, channelName);
	tmp->addMember(client);
	client->addChannel(tmp);
	client->sendMessage(RAW_JOIN(client->getNick(), client->getUser(), "nanachi", channelName));
	std::string name = "@" + client->getNick();
	// std::cout << "name: " << name << std::endl;
	client->sendMessage(RPL_NAMREPLY(client->getNick(), tmp->getChanName(), name));
	client->sendMessage(RPL_ENDOFNAMES(client->getNick(), tmp->getChanName()));
	_channels.push_back(tmp);
}
