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

bool	limiteCheck(const Channel *chan)
{
	if ((chan->getLimite() != 0 && chan->getLimite() <= chan->getClients().size()))
	{
		return (false);
	}
	return	(true);
}

bool	inviteCheck(Channel *chan, const Client *client)
{
	if (!chan->getInvite_only())
		return (true);
	for (unsigned int i = 0; i < chan->getGuests().size(); ++i)
	{
		if (chan->getGuests()[i] == client)
			return (true);
	}
	return (false);
}

void	joining(Channel *chan, Client *client)
{
	client->addChannel(chan);
	chan->addMember(client);
	for (unsigned int i = 0; i < chan->getClients().size(); ++i)
	{
		if (chan->getClients()[i] == client)
			continue;
		chan->getClients()[i]->sendMessage(RAW_JOIN(client->getNick(), client->getUser(), "nanachi", chan->getChanName()));
	}
	client->sendMessage(RAW_JOIN(client->getNick(), client->getUser(), "nanachi", chan->getChanName()));
}

void	actuNamesList(const Channel *chan, const Client *client)
{
	std::string names;
	if (chan->getOperator(chan->getClients()[0]))
		names += "@" + chan->getClients()[0]->getNick();
	else
		names += chan->getClients()[0]->getNick();
	for (unsigned int i = 1; i < chan->getClients().size(); ++i)
	{
		if (chan->getOperator(chan->getClients()[i]))
			names += " @" + chan->getClients()[i]->getNick();
		else
			names += " " + chan->getClients()[i]->getNick();
	}
	client->sendMessage(RPL_NAMREPLY(client->getNick(), chan->getChanName(), names));
	client->sendMessage(RPL_ENDOFNAMES(client->getNick(), chan->getChanName()));
}

void	IRCServ::CMDjoin(Client *client, std::string &buffer)
{
	if (!client->getIsRegister())
	{
		client->sendMessage(ERR_NOTREGISTERED);
		return;
	}
	const std::string channelName = buffer.substr(0, buffer.find_first_of(' '));
	nextArg(buffer);
	if (channelName[0] != '#' || !channelName[1])
		return;
	const std::string pwd = buffer.substr(0, buffer.find_first_of(' '));
	nextArg(buffer);
	for (unsigned int i = 0; i < client->getChannels().size(); ++i)
	{
		if (client->getChannels()[i]->getChanName() == channelName)
			 return;
	}
	Channel *chan = findChannel(channelName);
	if (chan != NULL)
	{
		if (!limiteCheck(chan))
		{
			client->sendMessage(ERR_CHANNELISFULL(channelName));
			return;
		}
		if (!inviteCheck(chan, client))
		{
			client->sendMessage(ERR_INVITEONLYCHAN(chan->getChanName()));
			return;
		}
		if (!chan->getPassword().empty() && pwd != chan->getPassword())
		{
			client->sendMessage(ERR_PASSWDMISMATCH);
			return;
		}
		joining(chan, client);
		actuNamesList(chan, client);
		if (!chan->getTopic().empty())
			client->sendMessage(RAW_TOPIC(client->getNick(), client->getUser(), "nanachi", chan->getChanName(), chan->getTopic()));
		return;
	}
	Channel *newChan = new Channel(client, channelName);
	newChan->addMember(client);
	joining(newChan, client);
	actuNamesList(newChan, client);
	_channels.push_back(newChan);
}
