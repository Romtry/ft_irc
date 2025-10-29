//
// Created by rothiery on 10/29/25.
//

#include "../../includes/defines.hpp"
#include "../../includes/IRCServ.hpp"

void IRCServ::CMDnick(unsigned int clientindex, std::string &buffer)
{
	buffer.erase(0, buffer.find(' '));
	for (unsigned int index = 0; buffer[index] == ' '; ++index)
		buffer.erase(0, 1);
	const std::string tmp = buffer.substr(0, buffer.find(' '));
	for (unsigned int i = 0; i < _clients.size(); ++i)
	{
		if (tmp == _clients[clientindex]->getNick())
		{
			
			return;
		}
	}

	_clients[clientindex]->setNick(tmp);
}
