/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdedola <rdedola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:30:11 by rdedola           #+#    #+#             */
/*   Updated: 2025/11/06 13:29:03 by rdedola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"

Channel::Channel(Client *member, const std::string &name)
	:	_chanName(name), _password(""), _topic(""), _limite(0), _invite_only(false)
{
	addMember(member);
	_operators.push_back(member->getNick());
}

void	Channel::addMember(Client *member)
{
	if (isMemmber(member->getNick()))
		return ;
	std::cout << member->getNick() << " trying to join limite: " << _limite << " nbr of members: " << _members.size() << std::endl;
	if (_limite == 0 || _limite < _members.size())
		_members.push_back(member);
}

void	Channel::removeMember(const Client *member)
{
	for (unsigned int i = 0; i < _members.size(); ++i)
	{
		if (member->getNick() == _members[i]->getNick())
		{
			_members.erase(_members.begin() + i);
			for (unsigned int j = 0; j < _members[i]->getChannels().size(); ++j)
			{
				if (_members[i]->getChannels()[j]->getChanName() == _chanName)
					_members[i]->getChannels().erase(_members[i]->getChannels().begin() + j);
			}
		}
	}
}

void	Channel::removeMember(const std::string& nick)
{
	for (unsigned int i = 0; i < _members.size(); ++i)
	{
		if (nick == _members[i]->getNick())
		{
			_members.erase(_members.begin() + i);
			for (unsigned int j = 0; j < _members[i]->getChannels().size(); ++j)
			{
				if (_members[i]->getChannels()[j]->getChanName() == _chanName)
					_members[i]->getChannels().erase(_members[i]->getChannels().begin() + j);
			}
		}
	}
}

bool Channel::getOperator(const std::string &Nick) const
{
	for (unsigned int i = 0; i < _operators.size(); ++i)
	{
		if (_operators[i] == Nick)
			return (true);
	}
	return (false);
}

bool	Channel::isMemmber(const std::string &nickName) const
{
	for (unsigned int i = 0; i < _members.size(); ++i)
	{
		if (nickName == _members[i]->getNick())
			return (true);
	}
	return (false);
}

