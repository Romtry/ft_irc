/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdedola <rdedola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:30:11 by rdedola           #+#    #+#             */
/*   Updated: 2026/02/06 11:20:33 by rdedola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"

Channel::Channel(Client *member, const std::string &name)
	:	_chanName(name), _password(""), _topic(""), _limite(0), _invite_only(false), _topicOpOnly(false)
{
	addMember(member);
	_operators.push_back(member);
}

void	Channel::addMember(Client *member)
{
	if (isMemmber(member))
		return ;
	_members.push_back(member);
}

void	Channel::removeMember(const Client *member)
{
	member->sendMessage(RAW_PART(member->getNick(), member->getUser(), "nanachi", _chanName, "part"));
	for (unsigned int i = 0; i < _members.size(); ++i)
	{
		if (member == _members[i])
		{
			_members.erase(_members.begin() + i);
			if (getOperator(member))
			{
				if (_operators.empty() && !_members.empty())
					addOperator(_members[0]);
			}
		}
		_members[i]->sendMessage(RAW_QUIT(member->getNick(), member->getUser(), "nanachi", "quit"));
	}

}

void Channel::removeOperator(const Client *client)
{
	for (unsigned int i = 0; i < _operators.size(); ++i)
	{
		if (_operators[i] == client)
		{
			_operators.erase(_operators.begin() + i);
			return ;
		}
	}
}

std::vector<Client *>	Channel::getOperators()
{
	return (_operators);
}

bool Channel::getOperator(const Client *client) const
{
	for (unsigned int i = 0; i < _operators.size(); ++i)
	{
		if (_operators[i] == client)
			return (true);
	}
	return (false);
}

bool	Channel::isMemmber(const Client *client) const
{
	for (unsigned int i = 0; i < _members.size(); ++i)
	{
		if (client == _members[i])
			return (true);
	}
	return (false);
}

void Channel::sendAll(const std::string &msg) const
{
	for (unsigned int i = 0; i < _members.size(); ++i)
	{
		_members[i]->sendMessage(msg);
	}
}
