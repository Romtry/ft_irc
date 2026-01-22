/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdedola <rdedola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:19:38 by rdedola           #+#    #+#             */
/*   Updated: 2025/10/30 13:54:18 by rdedola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IRCServ.hpp"
#include "Client.hpp"

class Client;

class Channel
{
	private:
		std::string					_chanName;
		std::string					_password;
		std::string					_topic;
		std::vector<Client *>		_members;
		std::vector<std::string>	_operators;
		std::vector<std::string>	_guests;
	
	public:
		Channel(Client *member, const std::string &name);
		~Channel() {};

		void			addMember(Client *member);
		void			removeMember(const Client *member);
		void			removeMember(const std::string &nick);
		bool			isMemmber(const std::string &nickName) const;

		std::vector<Client *>	getClients()	const	{return (_members);}
		std::string				getChanName()	const	{return (_chanName);}
		std::string				getPassword()	const	{return (_password);}
		std::string				getTopic()		const	{return (_topic);}
		bool					getOperator(const std::string &Nick) const;

		void			setChanName(const std::string chanName)	{_chanName = chanName;}
		void			setPassword(const std::string password)	{_password = password;}
		void			setTopic(const std::string topic)		{_topic = topic;}

	
};
