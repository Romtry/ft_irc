/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 10:02:51 by rothiery          #+#    #+#             */
/*   Updated: 2026/02/02 10:02:53 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/IRCServ.hpp"

void mode_exec(const Client *client, const unsigned int sign, const unsigned int index, Channel *channel, std::string &args)
{
	switch (index)
	{
		// i
		case 0:
		{
			if (!channel->getOperator(client))
				return;
			if (sign == '+')
			{
				channel->setInvite_only(true);
				if (!args.empty())
				{
					// sendmessage err

				}
			}
			else
				channel->setInvite_only(false);

		}
		// l
		case 1:
		{
			if (!channel->getOperator(client))
				return;
			if (sign == '-')
			{
				channel->setLimite(0);
				return;
			}
			if (args.empty())
			{
				client->sendMessage(ERR_NEEDMOREPARAMS);
				return;
			}
			const std::string arg = args.substr(0, args.find_first_of(' '));
			args.erase(0, args.find_first_of(' '));
			args.erase(0, args.find_first_not_of(' '));
			for (unsigned int i = 0; arg[i]; ++i)
			{
				if (!std::isdigit((arg[i])))
				{
					client->sendMessage(ERR_NEEDMOREPARAMS);
					return;
				}
			}
			const unsigned int num = strtoul(arg.c_str(), NULL, 0);
			if (num == 0)
			{
				client->sendMessage(ERR_NEEDMOREPARAMS);
				return;
			}
			channel->setLimite(num);
			return;
		}
		// o
		case 2:
		{
			if (channel->getOperator(client))
			{
				const std::string arg = args.substr(0, args.find_first_of(' '));
				args.erase(0, args.find_first_of(' '));
				args.erase(0, args.find_first_not_of(' '));
				for (unsigned int i = 0; i < channel->getClients().size(); ++i)
				{
					if (channel->getClients()[i]->getNick() == arg)
					{
						Client *target = channel->getClients()[i];
						if (sign == '+')
						{
							if (channel->getOperator(target))
								return ;
							channel->addOperator(target);
						}
						else
						{
							if (!channel->getOperator(target))
							{
								return ;
							}
							channel->removeOperator(target);
						}
						return;
					}
				}
				// snedmessage err
			}
			return;
		}
		// t
		case 3:
		{

		}
		// k
		case 4:
		{

		}
		default:
		{
			//sendmessage err
		}
	}
}

void	mode(const Client *Client, Channel *channel, const char sign, const std::string modes, std::string &args)
{
	char list[] = {'i', 'l', 'o', 't', 'k'};
	for (unsigned int i = 0; modes[i]; ++i)
	{
		unsigned int j = 0;
		while (list[j])
		{
			if (modes[i] == list[j])
			{
				mode_exec(Client, sign, j, channel, args);
				break;
			}
			++j;
		}
		if (!list[j])
		{
			//sedmessage err
		}
	}
}

void IRCServ::CMDmode(const Client *client, std::string &buffer)
{
	if (!client->getIsRegister())
	{
		client->sendMessage(ERR_NOTREGISTERED);
		return;
	}
	std::string channelName = buffer.substr(0, buffer.find_first_of(' '));
	if (channelName[0] != '#' || !channelName[1])
		return;
	channelName.erase(0, 1);
	buffer.erase(0, buffer.find_first_of(' '));
	buffer.erase(0, buffer.find_first_not_of(' '));
	const std::string modes = buffer.substr(0, buffer.find_first_of(' '));
	buffer.erase(0, buffer.find_first_of(' '));
	buffer.erase(0, buffer.find_first_not_of(' '));
	if (modes.size() < 2 || (modes[0] != '+' && modes[0] != '-'))
	{
		// sendmessage err
		return;
	}
	for (unsigned int i = 0; i < client->getChannels().size(); ++i)
	{
		if (client->getChannels()[i]->getChanName() == channelName)
		{
			if (client->getChannels()[i]->getOperator(client))
				mode(client, client->getChannels()[i], modes[0], modes.substr(1, modes.size() - 1), buffer);
			else
				//sendmessage err
			return;
		}
	}
}
