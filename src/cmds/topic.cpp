/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdedola <rdedola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:46:26 by rothiery          #+#    #+#             */
/*   Updated: 2026/02/06 12:17:23 by rdedola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/IRCServ.hpp"

void IRCServ::CMDtopic(const Client *client, std::string &buffer)
{
	if (!client->getIsRegister())
	{
		client->sendMessage(ERR_NOTREGISTERED);
		return;
	}
	std::string currentChanel = buffer.substr(0, buffer.find_first_of(' '));
	if (currentChanel[0] != '#' || !currentChanel[1])
		return;
	nextArg(buffer);
	for (unsigned int i = 0; i < client->getChannels().size(); ++i)
	{
		if (client->getChannels()[i]->getChanName() == currentChanel)
		{
			if (client->getChannels()[i]->getTopicOpOnly() && client->getChannels()[i]->getOperator(client))
			{
				if (!buffer.empty())
				{
					client->getChannels()[i]->setTopic(buffer);
					for (unsigned int j = 0; j < client->getChannels()[i]->getClients().size(); ++j)
					{
						client->getChannels()[i]->getClients()[j]->sendMessage(RAW_TOPIC(client->getNick(), client->getUser(), "nanachi", client->getChannels()[i]->getChanName(), buffer));
					}
				}
				else
				{
					if (client->getChannels()[i]->getTopic().empty())
						client->sendMessage(RPL_NOTOPIC(client->getNick(), client->getChannels()[i]->getChanName()));
					else
						client->sendMessage(RPL_TOPIC(client->getNick(), client->getChannels()[i]->getChanName(), client->getChannels()[i]->getTopic()));
				}
				return;
			}
			if (!client->getChannels()[i]->getTopicOpOnly())
			{
				// std::cout << "CHAN !OPONLY" << std::endl;
				if (!buffer.empty())
				{
					client->getChannels()[i]->setTopic(buffer);
					for (unsigned int j = 0; j < client->getChannels()[i]->getClients().size(); ++j)
					{
						client->getChannels()[i]->getClients()[j]->sendMessage(RAW_TOPIC(client->getNick(), client->getUser(), "nanachi", client->getChannels()[i]->getChanName(), buffer));
					}
				}
				else
				{
					if (client->getChannels()[i]->getTopic().empty())
						client->sendMessage(RPL_NOTOPIC(client->getNick(), client->getChannels()[i]->getChanName()));
					else
						client->sendMessage(RPL_TOPIC(client->getNick(), client->getChannels()[i]->getChanName(), client->getChannels()[i]->getTopic()));
				}
				return;
			}
			client->sendMessage(ERR_CHANOPRIVSNEEDED(client->getChannels()[i]->getChanName()));
			return ;
		}
	}
	client->sendMessage(ERR_NOSUCHCHANNEL(currentChanel));
}
