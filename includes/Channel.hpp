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
		unsigned int				_limite;
		bool						_invite_only;
	
	public:
		Channel(Client *member, const std::string &name);
		~Channel() {};

		void			addMember(Client *member);
		void			removeMember(const Client *member);
		void			removeMember(const std::string &nick);
		bool			isMemmber(const std::string &nickName) const;

		const std::vector<Client *>		&getClients()	const	{return (_members);}
		const std::string				&getChanName()	const	{return (_chanName);}
		const std::string				&getPassword()	const	{return (_password);}
		const std::string				&getTopic()		const	{return (_topic);}
		unsigned int			getLimite()		const	{return (_limite);}
		bool					getGuests();
		bool					getOperator(const std::string &Nick) const;
		bool					getInvite_only() const {return (_invite_only);}

		void			setLimite(const unsigned int limite) {_limite = limite;}
		void			setChanName(const std::string& chanName)	{_chanName = chanName;}
		void			setPassword(const std::string& password)	{_password = password;}
		void			setInvite_only(const bool b) {_invite_only = b;}
		void			setTopic(const std::string& topic)		{_topic = topic;}

	
};
