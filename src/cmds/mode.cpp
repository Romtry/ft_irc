/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdedola <rdedola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 10:02:51 by rothiery          #+#    #+#             */
/*   Updated: 2026/02/06 11:49:03 by rdedola          ###   ########.fr       */
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
			{
				client->sendMessage(ERR_CHANOPRIVSNEEDED(channel->getChanName()));
				return;
			}
			if (sign == '+')
			{
				channel->setInvite_only(true);
				channel->sendAll(RAW_MODE(client->getNick(), client->getUser(), "nanachi", channel->getChanName(), "+i", std::string("")));
			}
			else
			{
				channel->setInvite_only(false);
				channel->sendAll(RAW_MODE(client->getNick(), client->getUser(), "nanachi", channel->getChanName(), "-i", std::string("")));
			}
			return;
		}
		// l
		case 1:
		{
			if (!channel->getOperator(client))
			{
				client->sendMessage(ERR_CHANOPRIVSNEEDED(channel->getChanName()));
				return;
			}
			if (sign == '-')
			{
				channel->setLimite(0);
				channel->sendAll(RAW_MODE(client->getNick(), client->getUser(), "nanachi", channel->getChanName(), "-l", std::string("")));
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
			channel->sendAll(RAW_MODE(client->getNick(), client->getUser(), "nanachi", channel->getChanName(), "+l", std::string("")));
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
							channel->sendAll(RAW_MODE_ADDOP(client->getNick(), client->getUser(), "nanchi", channel->getChanName(), target->getNick()));
						}
						else
						{
							if (!channel->getOperator(target))
							{
								return ;
							}
							channel->removeOperator(target);
							channel->sendAll(RAW_MODE_REMOP(client->getNick(), client->getUser(), "nanchi", channel->getChanName(), target->getNick()));
						}
						return;
					}
				}
				client->sendMessage(ERR_NOSUCHNICK(arg));
				return;
			}
			client->sendMessage(ERR_CHANOPRIVSNEEDED(channel->getChanName()));
			return;
		}
		// t
		case 3:
		{
			if (!channel->getOperator(client))
			{
				client->sendMessage(ERR_CHANOPRIVSNEEDED(channel->getChanName()));
				return;
			}
			if (sign == '+')
			{
				channel->setTopicOpOnly(1);
				channel->sendAll(RAW_MODE(client->getNick(), client->getUser(), "nanachi", channel->getChanName(), "+t", std::string("")));
			}
			else
			{
				channel->setTopicOpOnly(0);
				channel->sendAll(RAW_MODE(client->getNick(), client->getUser(), "nanachi", channel->getChanName(), "-t", std::string("")));
			}
			return;
		}
		// k
		case 4:
		{
			if (!channel->getOperator(client))
			{
				client->sendMessage(ERR_CHANOPRIVSNEEDED(channel->getChanName()));
				return;
			}
			const std::string arg = args.substr(0, args.find_first_of(' '));
			args.erase(0, args.find_first_of(' '));
			args.erase(0, args.find_first_not_of(' '));
			if (sign == '+')
			{
				if (arg.empty())
					return;
				channel->setPassword(arg);
				channel->sendAll(RAW_MODE(client->getNick(), client->getUser(), "nanachi", channel->getChanName(), "+k", arg));
			}
			else
			{
				channel->setPassword("");
				channel->sendAll(RAW_MODE(client->getNick(), client->getUser(), "nanachi", channel->getChanName(), "-k", std::string("")));
			}
		}
		default:
		{
		}
	}
}

void	mode(const Client *client, Channel *channel, const char sign, const char *modes, std::string &args)
{
	char list[] = {'i', 'l', 'o', 't', 'k'};
	for (unsigned int i = 0; modes[i]; ++i)
	{
		unsigned int j = 0;
		while (list[j])
		{
			if (modes[i] == list[j])
			{
				mode_exec(client, sign, j, channel, args);
				break;
			}
			++j;
		}
		if (!list[j])
		{
			client->sendMessage(ERR_UNKNOWNMODE(modes[i]));
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
	nextArg(buffer);
	const std::string modes = buffer.substr(0, buffer.find_first_of(' '));
	nextArg(buffer);
	if (modes.size() < 2)
		return;
	if ((modes[0] != '+' && modes[0] != '-'))
	{
		client->sendMessage(ERR_UNKNOWNMODE(modes[0]));
		return;
	}
	for (unsigned int i = 0; i < client->getChannels().size(); ++i)
	{
		if (client->getChannels()[i]->getChanName() == channelName)
		{
			mode(client, client->getChannels()[i], modes[0], modes.substr(1, modes.size() - 1).c_str(), buffer);
			return;
		}
	}
}
