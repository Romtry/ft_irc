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

void IRCServ::CMDuser(Client *client, std::string &buffer)
{
	if (client->getUser() != "")
	{
		client->sendMessage(ERR_ALREADYREGISTRED);
		return;
	}
	const std::string tmp = buffer.substr(0, buffer.find(' '));
	client->setUser(tmp);
	std::cout << "Userset" << std::endl;
	buffer.erase(0, buffer.find(' '));
	if (buffer.substr(0, 7) != " 0 * : ")
		throw std::runtime_error("");
	buffer.erase(0, 7);
	client->setUser(buffer.substr(0, buffer.find(' ')));
	if (client->getNick() != "" && client->getPass())
		client->setIsRegister(true);
}
