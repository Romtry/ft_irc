/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdedola <rdedola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:27:45 by rdedola           #+#    #+#             */
/*   Updated: 2025/10/30 12:27:48 by rdedola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/defines.hpp"
#include "../../includes/IRCServ.hpp"

void IRCServ::CMDnick(Client *client, const std::string &buffer) const
{
	const std::string tmp = buffer.substr(0, buffer.find(' '));
	// std::cout << "" << std::endl;
	if (tmp.length() > 9 && !isalpha(tmp[0]))
	{
		client->sendMessage(ERR_ERRONEUSNICKNAME(tmp));
		return ;
	}
	// std::cout << "BUFFER OK" << std::endl;
	for (unsigned int i = 1; i < tmp.length(); ++i)
	{
		if (isalnum(tmp[i]) || tmp[i] == '-' || tmp[i] == '[' || tmp[i] == ']'
			|| tmp[i] == '\\' || tmp[i] == '`' || tmp[i] == '^' || tmp[i] == '{' || tmp[i] == '}')
			continue ;
		client->sendMessage(ERR_ERRONEUSNICKNAME(tmp));
		return ;
	}
	// std::cout << "VALID CHAR" << std::endl;
	for (unsigned int i = 0; i < _clients.size(); ++i)
	{
		if (tmp == _clients[i]->getNick())
		{
			client->sendMessage(ERR_NICKNAMEINUSE(tmp));
			return ;
		}
	}
	// std::cout << "BEFOR ALREADY VERIF" << std::endl;
	std::vector<Client *> already_send;
	for (unsigned int i = 0; i < client->getChannels().size(); ++i)
	{
		for (unsigned int j = 0; j < client->getChannels()[i]->getClients().size(); ++j)
		{
			bool already = false;
			for (unsigned int k = 0; k < already_send.size(); ++k)
			{
				if (already_send[k] == client->getChannels()[i]->getClients()[j])
				{
					already = true;
					break;
				}
			}
			if (already == true)
			{
				already = false;
				continue;
			}
			client->getChannels()[i]->getClients()[j]->sendMessage(RAW_NICKNAME(client->getNick(), tmp, client->getUser(), "nanachi"));
			already_send.push_back(client->getChannels()[i]->getClients()[j]);
		}
	}
	std::cout << "NICK CHANGED" << std::endl;
	client->sendMessage(RAW_NICKNAME(client->getNick(), tmp, client->getUser(), "nanachi"));
	client->setNick(tmp);
	if (client->getPass() && !client->getUser().empty())
	{
		std::cout << "REGISTERED" << std::endl;
		client->setIsRegister(true);
	}
}
