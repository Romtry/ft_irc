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
		return;
	unsigned int i = 0;
	std::string username = client->getTokens(1).substr(0, client->getTokens(1).find(' '));
	i = client->getTokens(1).find(' ', i);
	std::cout << "i: " << i << " token: " << client->getTokens(1).substr(i) << std::endl;
	i = client->getTokens(1).find(i, client->getTokens(1).find_first_not_of(' '));
	std::cout << "i: " << i << " token: " << client->getTokens(1) << std::endl;
	// if (client->getTokens(1)[i] != '0' || client->getTokens(1).find(' ', i) == std::string::npos)
	// 	return;
	// if (client->getTokens(1)[i + 1] != ' ')
	// 	return;
	// i = client->getTokens(1).find(i + 1, client->getTokens(1).find_first_not_of(' '));
	// if (client->getTokens(1)[i] != '*' || client->getTokens(1).find(' ', i) == std::string::npos)
	// 	return;
	// if (client->getTokens(1)[i + 1] != ' ')
	// 	return;
	// i = client->getTokens(1).find(i + 1, client->getTokens(1).find_first_not_of(' '));
	// if (client->getTokens(1)[i] != ':' || i + 1 == client->getTokens(1).size())
	// 	return;
	client->setUser(username);
	std::cout << "Userset" << std::endl;
}
