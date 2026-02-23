/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdedola <rdedola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:19:38 by rdedola           #+#    #+#             */
/*   Updated: 2026/02/06 11:51:15 by rdedola          ###   ########.fr       */
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
		std::vector<Client *>		_operators;
		std::vector<Client *>		_guests;
		unsigned int				_limite;
		bool						_invite_only;
		bool						_topicOpOnly;
	
	public:
		Channel(Client *member, const std::string &name);
		~Channel() {};

		void			addMember(Client *member);
		void			removeMember(const Client *member);
		void			removeOperator(const Client *client);
		bool			isMemmber(const Client *client) const;

		const std::vector<Client *>		&getClients()	const	{return (_members);}
		std::vector<Client *>			&getGuests()			{return (_guests);}
		const std::string				&getChanName()	const	{return (_chanName);}
		const std::string				&getPassword()	const	{return (_password);}
		const std::string				&getTopic()		const	{return (_topic);}
		unsigned int			getLimite()		const	{return (_limite);}
		bool					getOperator(const Client *client) const;
		bool					getInvite_only() const {return (_invite_only);}
		bool					getTopicOpOnly() const {return (_topicOpOnly);}

		void			sendAll(const std::string &msg) const;
		void			setLimite(const unsigned int limite) {_limite = limite;}
		void			setChanName(const std::string& chanName)	{_chanName = chanName;}
		void			setPassword(const std::string& password)	{_password = password;}
		void			setInvite_only(const bool b) {_invite_only = b;}
		void			setTopic(const std::string& topic)		{_topic = topic;}
		void			setTopicOpOnly(const bool b) {_topicOpOnly = b;}
		void			addOperator(Client *client)	{_operators.push_back((client));}
		void			addGuest(Client *client)	{_guests.push_back((client));}

	
};
