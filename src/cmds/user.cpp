//
// Created by rothiery on 10/29/25.
//

#include "../../includes/IRCServ.hpp"
#include "../../includes/defines.hpp"

void IRCServ::CMDuser(unsigned int clientindex, std::string &buffer)
{
	if (_clients[clientindex]->getUser() != "")
	{
		_clients[clientindex]->sendMessage(ERR_ALREADYREGISTRED);
		return;
	}
	const std::string tmp = buffer.substr(0, buffer.find(' '));
	_clients[clientindex]->setUser(tmp);
	std::cout << "Userset" << std::endl;
	buffer.erase(0, buffer.find(' '));
	if (buffer.substr(0, 7) != " 0 * : ")
		throw std::runtime_error("");
	buffer.erase(0, 7);
	_clients[clientindex]->setUser(buffer.substr(0, buffer.find(' ')));
	if (_clients[clientindex]->getNick() != "" && _clients[clientindex]->getPass())
		_clients[clientindex]->setIsRegister(true);
}
