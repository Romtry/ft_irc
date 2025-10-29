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
	if (_clients[clientindex]->getPass())
	{
		_clients[clientindex]->sendMessage(ERR_ALREADYREGISTRED);
		return;
	}
	// buffer.erase(0, buffer.find(' '));
	std::cout << "buffer = [" << buffer << "] psw = [" << _password << "]" << std::endl;
	if (buffer == _password)
	{
		_clients[clientindex]->setPass(true);
		if (_clients[clientindex]->getNick() != "" && _clients[clientindex]->getUser() != "" )
		{
			std::cout << "Password set" << std::endl;
			_clients[clientindex]->setIsRegister(true);
		}
	}
	else
		_clients[clientindex]->sendMessage(ERR_PASSWDMISMATCH);
}
