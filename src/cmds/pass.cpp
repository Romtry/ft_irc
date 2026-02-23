/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdedola <rdedola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:42:05 by rdedola           #+#    #+#             */
/*   Updated: 2025/10/29 14:14:23 by rdedola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRCServ.hpp"
#include "../../includes/defines.hpp"

void IRCServ::CMDpass(Client *client, const std::string &buffer) const
{
	if (client->getPass())
	{
		client->sendMessage(ERR_ALREADYREGISTRED);
		return;
	}
	if (buffer == _password)
	{
		client->setPass(true);
		if (!client->getNick().empty() && !client->getUser().empty() )
		{
			// std::cout << "REGISTERED" << std::endl;
			client->setIsRegister(true);
		}
	}
	else
		client->sendMessage(ERR_PASSWDMISMATCH);
}
