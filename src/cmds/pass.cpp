//
// Created by rothiery on 10/29/25.
//

#include "../../includes/IRCServ.hpp"
#include "../../includes/defines.hpp"

void IRCServ::CMDpass(unsigned int clientindex, std::string &buffer)
{
	buffer.erase(0, buffer.find(' '));
	for (unsigned int index = 0; buffer[index] == ' '; ++index)
		buffer.erase(0, 1);
	const std::string tmp = buffer.substr(0, buffer.find(' '));
	if (tmp == _password)
		_clients[clientindex]->setPass(true);
	else
		_clients[clientindex]->sendMessage(ERR_PASSWDMISMATCH);
}
