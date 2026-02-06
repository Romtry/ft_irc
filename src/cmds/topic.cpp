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
	buffer.erase(0, buffer.find_first_of(' '));
	buffer.erase(0, buffer.find_first_not_of(' '));
	std::cout << "HERE" << std::endl;
	for (unsigned int i = 0; i < client->getChannels().size(); ++i)
	{
		if (client->getChannels()[i]->getChanName() == currentChanel)
		{
			if (client->getChannels()[i]->getTopicOpOnly() && client->getChannels()[i]->getOperator(client))
			{
				if (!buffer.empty())
					client->getChannels()[i]->setTopic(buffer);
				else
					client->sendMessage(client->getChannels()[i]->getTopic());
				return;
			}
			else if (!client->getChannels()[i]->getTopicOpOnly())
			{
				if (!buffer.empty())
					client->getChannels()[i]->setTopic(buffer);
				else
					client->sendMessage(client->getChannels()[i]->getTopic());
				return;
			}
			else
			{
				std::cout << ERR_CHANOPRIVSNEEDED(client->getChannels()[i]->getChanName()) << std::endl;
				return ;
			}
		}
	}
	client->sendMessage(ERR_NOSUCHCHANNEL(currentChanel));
}
