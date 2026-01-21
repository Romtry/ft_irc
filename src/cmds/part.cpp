/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42nice.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:20:45 by rothiery          #+#    #+#             */
/*   Updated: 2026/01/21 15:20:45 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRCServ.hpp"

void IRCServ::CMDpart(Client *client, std::string &buffer) const
{
	if (!client->getisregister())
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
			std::vector<Channel *>::iterator it = client->getChannels().begin();
			for (unsigned int tmp = 0; tmp != i; ++tmp)
				++it;
			client->getChannels().erase(client->getChannels().begin() + i);
			return;
		}
	}
}
