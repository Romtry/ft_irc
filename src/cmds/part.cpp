/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:46:22 by rothiery          #+#    #+#             */
/*   Updated: 2026/01/22 11:46:24 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/IRCServ.hpp"

void IRCServ::CMDpart(Client *client, const std::string &buffer)
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
			client->getChannels()[i]->removeMember(client->getNick());
			return;
		}
	}
}
