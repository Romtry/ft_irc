/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdedola <rdedola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:27:55 by rdedola           #+#    #+#             */
/*   Updated: 2025/10/30 12:27:58 by rdedola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRCServ.hpp"
#include "../../includes/defines.hpp"

void IRCServ::CMDuser(Client *client)
{
	if (client->getUser() != "")
	{
		client->sendMessage(ERR_ALREADYREGISTRED);
		return;
	}
	if (client->getTokens(1).find(' ') == std::string::npos)
	{
		client->sendMessage(ERR_NEEDMOREPARAMS);
		return;
	}
	unsigned int i = 0;
	std::string username = client->getTokens(1).substr(0, client->getTokens(1).find(' '));
	std::cout << "user = " << username << std::endl;
	i = client->getTokens(1).find_first_not_of(' ', client->getTokens(1).find(' ', i));
	if (!client->getTokens(1)[i + 1] || client->getTokens(1).find(' ', i) == std::string::npos)
	{
		client->sendMessage(ERR_NEEDMOREPARAMS);
		return;
	}
	if (client->getTokens(1)[i] != '0')
		return;
	if (!client->getTokens(1)[i + 1] || client->getTokens(1).find(' ', i) == std::string::npos)
	{
		client->sendMessage(ERR_NEEDMOREPARAMS);
		return;
	}
	if (client->getTokens(1)[i + 1] != ' ')
		return;
	i = client->getTokens(1).find_first_not_of(' ', i + 1);
	if (!client->getTokens(1)[i + 1] || client->getTokens(1).find(' ', i) == std::string::npos)
	{
		client->sendMessage(ERR_NEEDMOREPARAMS);
		return;
	}
	if (client->getTokens(1)[i] != '*')
		return;
	if (!client->getTokens(1)[i + 1] || client->getTokens(1).find(' ', i) == std::string::npos)
	{
		client->sendMessage(ERR_NEEDMOREPARAMS);
		return;
	}
	if (client->getTokens(1)[i + 1] != ' ')
		return;
	i = client->getTokens(1).find_first_not_of(' ', i + 1);
	if (!client->getTokens(1)[i + 1])
	{
		client->sendMessage(ERR_NEEDMOREPARAMS);
		return;
	}
	if (client->getTokens(1)[i] != ':')
		return;
	client->setUser(username);
	if (client->getPass() && client->getNick() != "")
	{
		std::cout << "REGISTERED" << std::endl;
		client->setIsRegister(true);
	}
}