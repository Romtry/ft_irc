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

Channel::Channel(Client *member, std::string name)
	:	_chanName(name), _password(""), _topic(""), _userLimit(0)
{
	addMember(member);
}

void	Channel::addMember(Client *member)
{
	if (isMemmber(member->getNick()))
		return ;
	_members.push_back(member);
}

void	Channel::removeMember(Client *member)
{
	for (unsigned int i = 0; i < _members.size(); ++i)
	{
		if (member->getNick() == _members[i]->getNick())
		{
			_members.erase(_members.begin() + i);
		}
	}
	return ;
}

bool	Channel::isMemmber(const std::string &nickName)
{
	for (unsigned int i = 0; i < _members.size(); ++i)
	{
		if (nickName == _members[i]->getNick())
			return (true);
	}
	return (false);
}
