//
// Created by rothiery on 10/29/25.
//

#include "../../includes/defines.hpp"
#include "../../includes/IRCServ.hpp"

void IRCServ::CMDnick(unsigned int clientindex, std::string &buffer)
{
	if (_clients[clientindex]->getNick() != "")
	{
		_clients[clientindex]->sendMessage(ERR_ALREADYREGISTRED);
		return;
	}
	// buffer.erase(0, buffer.find(' '));
	const std::string tmp = buffer.substr(0, buffer.find(' '));
	for (unsigned int i = 0; i < _clients.size(); ++i)
	{
		if (tmp == _clients[clientindex]->getNick())
		{
			std::cout << ERR_NICKNAMEINUSE(tmp) << std::endl;
			return;
		}
	}

	_clients[clientindex]->setNick(tmp);
}
