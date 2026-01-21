/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42nice.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:30:32 by rothiery          #+#    #+#             */
/*   Updated: 2026/01/21 10:30:32 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRCServ.hpp"

void IRCServ::CMDtopic(const Client *client, std::string &buffer) const
{
	if (!client->getisregister())
	{
		client->sendMessage(ERR_NOTREGISTERED);
		return;
	}
	std::string currentChanel = buffer.substr(0, buffer.find_first_of(' '));
	if (currentChanel[0] != '#' || !currentChanel[1])
		return;
	currentChanel.erase(0, 1);
	buffer.erase(0, buffer.find_first_of(' '));
	buffer.erase(0, buffer.find_first_not_of(' '));
	unsigned int i = 0;
	while (i < client->getChannels().size())
	{
		if (client->getChannels()[i]->getChanName() == currentChanel)
			break;
	}
	if (i == client->getChannels().size())
	{
		client->sendMessage(ERR_NOSUCHCHANNEL(currentChanel));
		return;
	}
	if (!buffer.empty())
		client->getChannels()[i]->setTopic(buffer);
	else
		client->sendMessage(client->getChannels()[i]->getTopic());
}
