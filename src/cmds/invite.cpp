/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdedola <rdedola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:42:38 by rdedola           #+#    #+#             */
/*   Updated: 2026/02/04 14:07:16 by rdedola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Channel.hpp"
#include "../../includes/IRCServ.hpp"

void	IRCServ::CMDinvite(Client *client, std::string &buffer)
{
	if (!client->getIsRegister())
	{
		client->sendMessage(ERR_NOTREGISTERED);
		return ;
	}

	const std::string	name = buffer.substr(0, buffer.find_first_of(' '));
	buffer.erase(0, buffer.find_first_of(' '));
	buffer.erase(0, buffer.find_first_not_of(' '));
	const std::string	chan = buffer.substr(0, buffer.find_first_of(' '));
	buffer.erase(0, buffer.find_first_of(' '));
	buffer.erase(0, buffer.find_first_not_of(' '));
	
	if (buffer.size() > 0)
		return ;

	Client *target = NULL;
	for (unsigned int i = 0; i < _clients.size(); ++i)
	{
		if (name == _clients[i]->getNick())
		{
			target = _clients[i];
			break ;
		}
	}

	if (!target)
	{
		// ! put error msg !!
		std::cout << "NO TARGET" << std::endl;
		return ;
	}

	for (unsigned int i = 0; i < _channels.size(); ++i)
	{
		if (chan == _channels[i]->getChanName())
		{
			_channels[i]->addGuest(target);
		}
	}
}
