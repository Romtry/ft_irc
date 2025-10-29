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

void IRCServ::CMDpass(unsigned int clientindex, std::string &buffer)
{
	// buffer.erase(0, buffer.find(' '));
	for (unsigned int index = 0; buffer[index] == ' '; ++index)
		buffer.erase(0, 1);
	const std::string tmp = buffer.substr(0, buffer.find(' '));
	if (tmp == _password)
	{
		_clients[clientindex]->setPass(true);
		if (_clients[clientindex]->getNick() != "" && _clients[clientindex]->getUser() != "" )
			_clients[clientindex]->setIsRegister(true);
	}
	else
		_clients[clientindex]->sendMessage(ERR_PASSWDMISMATCH);
}
