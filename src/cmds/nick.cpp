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
	if (tmp.length() > 9 && !isalpha(tmp[0]))
	{
		_clients[clientindex]->sendMessage(ERR_ERRONEUSNICKNAME(tmp));
		return ;
	}
	for (unsigned int i = 1; i < tmp.length(); ++i)
	{
		if (isalnum(tmp[i]) || tmp[i] == '-' || tmp[i] == '[' || tmp[i] == ']'
			|| tmp[i] == '\\' || tmp[i] == '`' || tmp[i] == '^' || tmp[i] == '{' || tmp[i] == '}')
			break ;
		else
		{
			_clients[clientindex]->sendMessage(ERR_ERRONEUSNICKNAME(tmp));
			return ;
		}
	}
	for (unsigned int i = 0; i < _clients.size(); ++i)
	{
		if (tmp == _clients[i]->getNick())
		{
			_clients[clientindex]->sendMessage(ERR_NICKNAMEINUSE(tmp));
			return ;
		}
	}
	_clients[clientindex]->setNick(tmp);
}
