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

void IRCServ::CMDnick(Client *client, const std::string &buffer)
{
	if (client->getNick() != "")
	{
		client->sendMessage(ERR_ALREADYREGISTRED);
		return;
	}
	const std::string tmp = buffer.substr(0, buffer.find(' '));
	if (tmp.length() > 9 && !isalpha(tmp[0]))
	{
		client->sendMessage(ERR_ERRONEUSNICKNAME(tmp));
		return ;
	}
	for (unsigned int i = 1; i < tmp.length(); ++i)
	{
		if (isalnum(tmp[i]) || tmp[i] == '-' || tmp[i] == '[' || tmp[i] == ']'
			|| tmp[i] == '\\' || tmp[i] == '`' || tmp[i] == '^' || tmp[i] == '{' || tmp[i] == '}')
			continue ;
		else
		{
			client->sendMessage(ERR_ERRONEUSNICKNAME(tmp));
			return ;
		}
	}
	for (unsigned int i = 0; i < _clients.size(); ++i)
	{
		if (tmp == _clients[i]->getNick())
		{
			client->sendMessage(ERR_NICKNAMEINUSE(tmp));
			return ;
		}
	}
	client->setNick(tmp);
	if (client->getPass() && client->getUser() != "")
	{
		std::cout << "REGISTERED" << std::endl;
		client->setIsRegister(true);
	}
}
