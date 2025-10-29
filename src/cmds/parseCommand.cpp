//
// Created by rothiery on 10/24/25.
//

#include <algorithm>

#include "../../includes/defines.hpp"
#include "../../includes/IRCServ.hpp"


void IRCServ::parseCommand(unsigned int clientindex, std::string &buffer)
{
	for (unsigned int index = 0; buffer[index] == ' '; ++index)
		buffer.erase(0, 1);
	std::string tmp = buffer.substr(0, buffer.find(' '));
	if (tmp == "PASS")
		IRCServ::CMDpass(clientindex, buffer);
	else if (tmp == "NICK")
		IRCServ::CMDnick(clientindex, buffer);
	else if (tmp != "CAP")
	{
		std::cout << "Wrong command" << std::endl;
	}
}
