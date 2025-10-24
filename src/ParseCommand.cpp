//
// Created by rothiery on 10/24/25.
//

#include <algorithm>

#include "../includes/defines.hpp"
#include "../includes/ircserv.hpp"


void ircserv::ParseCommand(unsigned int i, std::string &buffer)
{
	for (unsigned int index = 0; buffer[index] == ' '; ++index)
		buffer.erase(0, 1);
	std::string tmp = buffer.substr(0, buffer.find(' '));
	if (tmp == "CAP")
		return;
	if (tmp == "PASS")
	{
		buffer.erase(0, buffer.find(' '));
		for (unsigned int index = 0; buffer[index] == ' '; ++index)
			buffer.erase(0, 1);
		tmp = buffer.substr(0, buffer.find(' '));
		if (tmp == _password)
			_clients[i].setPass(true);
		else
			_clients[i].sendMessage(ERR_PASSWDMISMATCH);
		return;
	}
}
