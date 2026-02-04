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
	std::cout << std::endl << "IN INVITE" << std::endl;
	const std::string	name = buffer.substr(0, buffer.find_first_of(' '));
	buffer.erase(0, buffer.find_first_of(' '));
	buffer.erase(0, buffer.find_first_not_of(' '));
	std::string	chan = buffer.substr(0, buffer.find_first_of(' '));
	buffer.erase(0, buffer.find_first_of(' '));
	buffer.erase(0, buffer.find_first_not_of(' '));
	if (chan[0] != '#' || !chan[1])
		return;
	chan.erase(0, 1);
	
	// if (buffer.size() > 0)
	// {
	// 	std::cout << "REMY DU TALMUD" << std::endl;
	// 	return ;
	// }

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
		std::cout << chan << " != " << _channels[i]->getChanName() << std::endl;
		if (chan == _channels[i]->getChanName())
		{
			std::cout << "ADDGUEST" << std::endl;
			_channels[i]->addGuest(target);
			return;
		}
	}
	std::cout << "CHANNEL NOT FOUND" << std::endl;
}
